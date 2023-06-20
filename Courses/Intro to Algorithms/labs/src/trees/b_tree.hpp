#pragma once
#include "../utils.hpp"
#include "base.hpp"

template <typename T, size_t M> struct BTreeNode {
  T keys[M - 1];
  BTreeNode *children[M];
  BTreeNode *parent = nullptr;
  int size = 0;
  bool is_leaf() const { return children[0] == nullptr; }
  int index() const {
    if (parent == nullptr)
      return -1;
    int i = utils::lower_bound(parent->keys, parent->size, keys[0]);
    while (parent->children[i] != this)
      ++i;
    return i;
  }
  friend ostream &operator<<(ostream &os, const BTreeNode &node) {
    os << &node << ',' << node.parent;
    for (int i = 0; i < M - 1; ++i)
      os << ',' << node.keys[i];
    for (int i = 0; i < M; ++i)
      os << ',' << node.children[i];
    os << ',' << node.size;
    return os;
  }
};

template <typename T, size_t M> class BTree : public SearchTreeInterface<T> {
  static_assert(M >= 3);
  using Node = BTreeNode<T, M>;

protected:
  const int l_size = (M - 1) / 2, r_size = M / 2;

  Node *root_ = new Node;

  void insert_child(Node *node, int i, Node *c) {
    for (int j = node->size; j >= i; --j)
      node->children[j + 1] = node->children[j];
    node->children[i] = c;
    c->parent = node;
  }

  void insert_item(Node *node, int i, const T &key) {
    for (int j = node->size - 1; j >= i; --j)
      node->keys[j + 1] = node->keys[j];
    node->keys[i] = key;
  }

  void delete_item(Node *node, int i) {
    for (int j = i; j < node->size - 1; ++j)
      node->keys[j] = node->keys[j + 1];
    node->keys[node->size - 1] = T();
  }

  void delete_child(Node *node, int i) {
    for (int j = i; j < node->size; ++j)
      node->children[j] = node->children[j + 1];
    node->children[node->size] = nullptr;
  }

  void move_item(Node *src, int i, T &key) {
    key = src->keys[i];
    src->keys[i] = T();
  }

  void move_child(Node *src, int i, Node *dst, int j) {
    Node *c = src->children[i];
    dst->children[j] = c;
    c->parent = dst;
    src->children[i] = nullptr;
  }

  /*
    ⚠️ Deprecated: Top-down split does not work for odd-order B-tree!
  */
  // void split_child(Node *node, int i) {
  //   Node *c = node->children[i], *nc = new Node;
  //   c->size = M / 2 - 1;
  //   nc->size = (M - 1) / 2;
  //   for (int j = 0; j < (M - 1) / 2; ++j)
  //     nc->keys[j] = c->keys[j + M / 2];
  //   if (!c->is_leaf())
  //     for (int j = 0; j < (M + 1) / 2; ++j)
  //       set_child(nc, j, c->children[j + M / 2]);
  //   insert_item(node, i, c->keys[M / 2 - 1]);
  //   insert_child(node, i + 1, nc);
  //   ++node->size;
  // }
  //
  // enum SearchFlags : char { SPLIT = 1 << 0, LEAF = 1 << 1 };
  // Node *search_node(const T &key, char flags) {
  //   if (flags & SPLIT && root_->size == M - 1) {
  //     Node *new_root = new Node;
  //     insert_child(new_root, 0, root_);
  //     split_child(new_root, 0);
  //     root_ = new_root;
  //   }
  //   Node *node = root_;
  //   while (!node->is_leaf()) {
  //     int i = utils::lower_bound(node->keys, node->size, key);
  //     if (!(flags & LEAF) && i < node->size && node->keys[i] == key)
  //       return node;
  //     if (flags & SPLIT && node->children[i]->size == M - 1) {
  //       split_child(node, i);
  //       node = node->keys[i] < key ? node->children[i + 1] :
  //       node->children[i]; continue;
  //     }
  //     node = node->children[i];
  //   }
  //   return node;
  // }
  //
  // Node *search_node(const T &key, char flags = 0) const {
  //   return const_cast<BTree *>(this)->search_node(key, flags);
  // }

  Node *search_node(const T &key) const {
    Node *node = root_;
    while (node != nullptr) {
      int i = utils::lower_bound(node->keys, node->size, key);
      if (i < node->size && node->keys[i] == key)
        return node;
      node = node->children[i];
    }
    return nullptr;
  }

  Node *search_leaf(const T &key) const {
    Node *node = root_;
    while (!node->is_leaf())
      node = node->children[utils::lower_bound(node->keys, node->size, key)];
    return node;
  }

  Node *split_node(Node *node, int i, T &key, Node *child) {
    Node *new_node = new Node;
    node->size = l_size;
    new_node->size = r_size;
    if (i == l_size) {
      // key is the median
      for (int j = 0; j < r_size; ++j)
        move_item(node, j + l_size, new_node->keys[j]);
      if (!node->is_leaf()) {
        for (int j = 0; j < r_size; ++j)
          move_child(node, j + l_size + 1, new_node, j);
        insert_child(new_node, 0, child);
      }
    } else if (i < l_size) {
      // key should be inserted into the left `node`
      for (int j = 0; j < r_size; ++j)
        move_item(node, j + l_size, new_node->keys[j]);
      insert_item(node, i, key);
      move_item(node, l_size, key);
      if (!node->is_leaf()) {
        for (int j = 0; j <= r_size; ++j)
          move_child(node, j + l_size, new_node, j);
        insert_child(node, i + 1, child);
      }
    } else {
      // key should be inserted into the right `new_node`
      for (int j = 0; j < r_size - 1; ++j)
        move_item(node, j + l_size + 1, new_node->keys[j]);
      insert_item(new_node, i - l_size - 1, key);
      move_item(node, l_size, key);
      if (!node->is_leaf()) {
        for (int j = 0; j < r_size; ++j)
          move_child(node, j + l_size + 1, new_node, j);
        insert_child(new_node, i - l_size, child);
      }
    }
    return new_node;
  }

  bool rebalance_child(Node *p, int i) {
    Node *node = p->children[i];
    Node *ls = i > 0 ? p->children[i - 1] : nullptr;
    Node *rs = i < p->size ? p->children[i + 1] : nullptr;
    if (ls && ls->size > (M - 1) / 2) {
      // borrow from left sibling
      insert_item(node, 0, p->keys[i - 1]);
      move_item(ls, ls->size - 1, p->keys[i - 1]);
      if (!node->is_leaf()) {
        insert_child(node, 0, ls->children[ls->size]);
        delete_child(ls, ls->size);
      }
      ++node->size;
      --ls->size;
      return true;
    }
    if (rs && rs->size > (M - 1) / 2) {
      // borrow from right sibling
      insert_item(node, (M - 1) / 2 - 1, p->keys[i]);
      move_item(rs, 0, p->keys[i]);
      delete_item(rs, 0);
      if (!node->is_leaf()) {
        insert_child(node, (M - 1) / 2, rs->children[0]);
        delete_child(rs, 0);
      }
      ++node->size;
      --rs->size;
      return true;
    }
    if (ls) {
      // merge with left sibling
      insert_item(ls, ls->size, p->keys[i - 1]);
      for (int j = 0; j < node->size; ++j)
        move_item(node, j, ls->keys[ls->size + j + 1]);
      if (!node->is_leaf())
        for (int j = 0; j <= node->size; ++j)
          move_child(node, j, ls, ls->size + j + 1);
      ls->size += node->size + 1;
      delete_item(p, i - 1);
      delete_child(p, i);
      delete node;
    } else if (rs) {
      // merge with right sibling
      insert_item(node, node->size, p->keys[i]);
      for (int j = 0; j < rs->size; ++j)
        move_item(rs, j, node->keys[node->size + j + 1]);
      if (!node->is_leaf())
        for (int j = 0; j <= rs->size; ++j)
          move_child(rs, j, node, node->size + j + 1);
      node->size += rs->size + 1;
      delete_item(p, i);
      delete_child(p, i + 1);
      delete rs;
    } else {
      // special case for M <= 4
      insert_item(node, node->size, p->keys[i]);
      delete_item(p, i);
      delete_child(p, i + 1);
    }
    return false;
  }

public:
  BTree() = default;
  ~BTree() override { clear(); }
  void clear() override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return;
      for (int i = 0; i <= node->size; ++i)
        traverse(node->children[i]);
      delete node;
    };
  }

  /*
    ⚠️ Deprecated: Top-down split does not work for odd-order B-tree!
  */
  // void insert(const T &key) override {
  //   Node *node = search_node(key, SPLIT | LEAF);
  //   int i = utils::lower_bound(node->keys, node->size, key);
  //   insert_item(node, i, key);
  //   ++node->size;
  // }

  void insert(const T &key_) override {
    T key = key_;
    Node *node = search_leaf(key);
    int i = utils::lower_bound(node->keys, node->size, key);
    if (node->size < M - 1) {
      insert_item(node, i, key);
      ++node->size;
      return;
    }
    Node *child = nullptr;
    while (node->size == M - 1) {
      if (node == root_) {
        Node *new_root = new Node;
        insert_child(new_root, 0, root_);
        root_ = new_root;
      }
      child = split_node(node, i, key, child);
      i = node->index();
      node = node->parent;
    }
    insert_item(node, i, key);
    insert_child(node, i + 1, child);
    ++node->size;
  }

  void remove(const T &key) override {
    Node *node = search_node(key);
    if (node == nullptr)
      return;
    int i = utils::lower_bound(node->keys, node->size, key);
    if (node->is_leaf())
      delete_item(node, i);
    else if (i < node->size - 1) {
      // delete successor
      Node *succ = node->children[i + 1];
      while (!succ->is_leaf())
        succ = succ->children[0];
      move_item(succ, 0, node->keys[i]);
      delete_item(succ, 0);
      node = succ;
    } else {
      // delete predecessor
      Node *pred = node->children[i];
      while (!pred->is_leaf())
        pred = pred->children[pred->size];
      move_item(pred, pred->size - 1, node->keys[i]);
      node = pred;
    }
    --node->size;
    while (node->size < (M - 1) / 2) {
      if (node == root_) {
        // root is empty
        if (!node->is_leaf() && node->size == 0) {
          root_ = node->children[0];
          delete node;
        }
        break;
      }
      i = node->index();
      Node *p = node->parent;
      if (rebalance_child(p, i))
        break;
      --p->size;
      node = p;
    }
  }

  bool contains(const T &key) const override {
    return search_node(key) != nullptr;
  }

  int height() const override {
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      int h = 0;
      if (!node->is_leaf())
        for (int i = 0; i <= node->size; ++i)
          h = max(h, traverse(node->children[i]));
      return h + 1;
    };
    return traverse(root_);
  }

  int size() const override {
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      int s = node->size;
      if (!node->is_leaf())
        for (int i = 0; i <= node->size; ++i)
          s += traverse(node->children[i]);
      return s;
    };
    return traverse(root_);
  }

  bool empty() const override { return root_->size == 0; }

  vector<T> values() const override {
    vector<T> values;
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr || node->size == 0)
        return;
      traverse(node->children[0]);
      values.push_back(node->keys[0]);
      for (int i = 1; i < node->size; ++i) {
        traverse(node->children[i]);
        values.push_back(node->keys[i]);
      }
      traverse(node->children[node->size]);
    };
    traverse(root_);
    return values;
  }

  void print(ostream &os, const string &indent = "") const override {
    int depth = -1;
    function<string()> prefix = [&]() {
      return indent + string(depth * 3, ' ') + "|- ";
    };
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return;
      ++depth;
      os << prefix() << node->keys[0] << endl;
      traverse(node->children[0]);
      for (int i = 1; i < node->size; ++i) {
        os << prefix() << node->keys[i - 1] << '<' << node->keys[i] << endl;
        traverse(node->children[i]);
      }
      os << prefix() << node->keys[node->size - 1] << endl;
      traverse(node->children[node->size]);
      --depth;
    };
    traverse(root_);
  }

  void print_csv(ostream &os, const string &indent = "") const override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      os << indent << *node << endl;
      if (!node->is_leaf())
        for (int i = 0; i <= node->size; ++i)
          traverse(node->children[i]);
    };
    traverse(root_);
  }

  bool check() const override {
    function<bool(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node != root_ && node->size < (M - 1) / 2)
        return false;
      if (!node->is_leaf())
        for (int i = 0; i <= node->size; ++i)
          if (!traverse(node->children[i]))
            return false;
      return true;
    };
    return traverse(root_);
  }
};
