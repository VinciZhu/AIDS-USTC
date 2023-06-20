#pragma once
#include "../utils.hpp"
#include "base.hpp"

template <typename T, size_t M> struct BPlusTreeNode;
template <typename T, size_t M>
struct BPlusTreeLeaf : public BPlusTreeNode<T, M> {
  BPlusTreeLeaf *prev = nullptr, *next = nullptr;
  BPlusTreeLeaf() { this->is_leaf = true; }
  friend ostream &operator<<(ostream &os, const BPlusTreeLeaf &leaf) {
    os << &leaf << ',' << leaf.parent;
    for (int i = 0; i < M; ++i)
      os << ',' << leaf.keys[i];
    os << ",0x0," << leaf.prev << ',' << leaf.next;
    for (int i = 3; i < M; ++i)
      os << ",0x0";
    os << ',' << leaf.size;
    return os;
  }
};

template <typename T, size_t M>
struct BPlusTreeNonleaf : public BPlusTreeNode<T, M> {
  BPlusTreeNode<T, M> *children[M + 1];
  BPlusTreeNonleaf() { this->is_leaf = false; }
  friend ostream &operator<<(ostream &os, const BPlusTreeNonleaf &nonleaf) {
    os << &nonleaf << ',' << nonleaf.parent;
    for (int i = 0; i < M; ++i)
      os << ',' << nonleaf.keys[i];
    for (int i = 0; i < M; ++i)
      os << ',' << nonleaf.children[i];
    os << ',' << nonleaf.size;
    return os;
  }
};

template <typename T, size_t M> struct BPlusTreeNode {
  T keys[M];
  BPlusTreeNonleaf<T, M> *parent = nullptr;
  int size = 0;
  bool is_leaf;
  const T &max_key() const { return keys[size - 1]; }
  int index() const {
    if (parent == nullptr)
      return -1;
    int i = utils::lower_bound(parent->keys, parent->size, keys[0]);
    while (parent->children[i] != this)
      ++i;
    return i;
  }
};

template <typename T, size_t M>
class BPlusTree : public SearchTreeInterface<T> {
  static_assert(M >= 3);
  using Node = BPlusTreeNode<T, M>;
  using Leaf = BPlusTreeLeaf<T, M>;
  using Nonleaf = BPlusTreeNonleaf<T, M>;

protected:
  const int l_size = (M + 1) / 2, r_size = (M + 2) / 2;

  Leaf *head_ = new Leaf;
  Node *root_ = head_;

  void connect(Leaf *prev, Leaf *next) {
    if (prev != nullptr)
      prev->next = next;
    if (next != nullptr)
      next->prev = prev;
  }

  void update_key(Nonleaf *nonleaf, int i) {
    nonleaf->keys[i] = nonleaf->children[i]->max_key();
  }

  void insert_child(Nonleaf *nonleaf, int i, Node *c) {
    for (int j = nonleaf->size; j > i; --j) {
      nonleaf->children[j] = nonleaf->children[j - 1];
      nonleaf->keys[j] = nonleaf->keys[j - 1];
    }
    nonleaf->children[i] = c;
    nonleaf->keys[i] = c->max_key();
    c->parent = nonleaf;
  }

  void insert_item(Leaf *leaf, int i, const T &key) {
    for (int j = leaf->size; j > i; --j)
      leaf->keys[j] = leaf->keys[j - 1];
    leaf->keys[i] = key;
  }

  void delete_child(Nonleaf *nonleaf, int i) {
    for (int j = i; j < nonleaf->size - 1; ++j) {
      nonleaf->children[j] = nonleaf->children[j + 1];
      nonleaf->keys[j] = nonleaf->keys[j + 1];
    }
    nonleaf->children[nonleaf->size - 1] = nullptr;
    nonleaf->keys[nonleaf->size - 1] = T();
  }

  void delete_item(Leaf *leaf, int i) {
    for (int j = i; j < leaf->size - 1; ++j)
      leaf->keys[j] = leaf->keys[j + 1];
    leaf->keys[leaf->size - 1] = T();
  }

  void move_child(Nonleaf *src, int i, Nonleaf *dst, int j) {
    Node *c = src->children[i];
    dst->children[j] = c;
    dst->keys[j] = c->max_key();
    c->parent = dst;
    src->children[i] = nullptr;
    src->keys[i] = T();
  }

  void move_item(Leaf *src, int i, T &key) {
    key = src->keys[i];
    src->keys[i] = T();
  }

  Leaf *search_leaf(const T &key) const {
    if (root_->is_leaf)
      return static_cast<Leaf *>(root_);
    Node *node = root_;
    while (!node->is_leaf)
      node = static_cast<Nonleaf *>(node)->children[min(
          utils::lower_bound(node->keys, node->size, key), node->size - 1)];
    return static_cast<Leaf *>(node);
  }

  Leaf *split_leaf(Leaf *leaf, int i, const T &key) {
    Leaf *new_leaf = new Leaf;
    leaf->size = l_size;
    new_leaf->size = r_size;
    if (i < l_size) {
      // key should be inserted into the left `leaf`
      for (int j = 0; j < r_size; ++j)
        move_item(leaf, j + l_size - 1, new_leaf->keys[j]);
      insert_item(leaf, i, key);
    } else {
      // key should be inserted into the right `new_leaf`
      for (int j = 0; j < r_size - 1; ++j)
        move_item(leaf, j + l_size, new_leaf->keys[j]);
      insert_item(new_leaf, i - l_size, key);
    }
    connect(new_leaf, leaf->next);
    connect(leaf, new_leaf);
    return new_leaf;
  }

  Nonleaf *split_nonleaf(Nonleaf *nonleaf, int i, Node *child) {
    Nonleaf *new_nonleaf = new Nonleaf;
    nonleaf->size = l_size;
    new_nonleaf->size = r_size;
    if (i < l_size) {
      // child should be inserted into the left `nonleaf`
      for (int j = 0; j < r_size; ++j)
        move_child(nonleaf, j + l_size - 1, new_nonleaf, j);
      insert_child(nonleaf, i, child);
    } else {
      // child should be inserted into the right `new_nonleaf`
      for (int j = 0; j < r_size - 1; ++j)
        move_child(nonleaf, j + l_size, new_nonleaf, j);
      insert_child(new_nonleaf, i - l_size, child);
    }
    return new_nonleaf;
  }

  bool rebalance_leaf(Leaf *leaf, int &i) {
    Nonleaf *p = leaf->parent;
    Leaf *ls = nullptr, *rs = nullptr;
    if (i > 0) {
      ls = static_cast<Leaf *>(p->children[i - 1]);
      if (ls->size > M / 2) {
        // borrow from left sibling
        insert_item(leaf, 0, ls->keys[ls->size - 1]);
        delete_item(ls, ls->size - 1);
        ++leaf->size;
        --ls->size;
        update_key(p, i - 1);
        return true;
      }
    }
    if (i < p->size - 1) {
      rs = static_cast<Leaf *>(p->children[i + 1]);
      if (rs->size > M / 2) {
        // borrow from right sibling
        insert_item(leaf, leaf->size, rs->keys[0]);
        delete_item(rs, 0);
        ++leaf->size;
        --rs->size;
        update_key(p, i);
        return true;
      }
    }
    if (ls) {
      // merge with left sibling
      for (int j = 0; j < leaf->size; ++j)
        move_item(leaf, j, ls->keys[ls->size + j]);
      connect(ls, leaf->next);
      ls->size += leaf->size;
      delete leaf;
      delete_child(p, i--);
    } else {
      // merge with right sibling
      for (int j = 0; j < rs->size; ++j)
        move_item(rs, j, leaf->keys[leaf->size + j]);
      connect(leaf, rs->next);
      leaf->size += rs->size;
      delete rs;
      delete_child(p, i + 1);
    }
    --p->size;
    update_key(p, i);
    return false;
  }

  bool rebalance_nonleaf(Nonleaf *nonleaf, int &i) {
    Nonleaf *p = nonleaf->parent;
    Nonleaf *ls = nullptr, *rs = nullptr;
    if (i > 0) {
      ls = static_cast<Nonleaf *>(p->children[i - 1]);
      if (ls->size > M / 2) {
        // borrow from left sibling
        insert_child(nonleaf, 0, ls->children[ls->size - 1]);
        delete_child(ls, ls->size - 1);
        ++nonleaf->size;
        --ls->size;
        update_key(p, i - 1);
        return true;
      }
    }
    if (i < p->size - 1) {
      rs = static_cast<Nonleaf *>(p->children[i + 1]);
      if (rs->size > M / 2) {
        // borrow from right sibling
        insert_child(nonleaf, nonleaf->size, rs->children[0]);
        delete_child(rs, 0);
        ++nonleaf->size;
        --rs->size;
        update_key(p, i);
        return true;
      }
    }
    if (ls) {
      // merge with left sibling
      for (int j = 0; j < nonleaf->size; ++j)
        move_child(nonleaf, j, ls, ls->size + j);
      ls->size += nonleaf->size;
      delete nonleaf;
      delete_child(p, i--);
    } else {
      // merge with right sibling
      for (int j = 0; j < rs->size; ++j)
        move_child(rs, j, nonleaf, nonleaf->size + j);
      nonleaf->size += rs->size;
      delete rs;
      delete_child(p, i + 1);
    }
    --p->size;
    update_key(p, i);
    return false;
  }

  bool rebalance_child(Nonleaf *nonleaf, int &i) {
    Node *child = nonleaf->children[i];
    if (child->is_leaf)
      return rebalance_leaf(static_cast<Leaf *>(child), i);
    else
      return rebalance_nonleaf(static_cast<Nonleaf *>(child), i);
  }

public:
  BPlusTree() = default;
  ~BPlusTree() override { clear(); }
  void clear() override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node->is_leaf) {
        delete static_cast<Leaf *>(node);
        return;
      }
      Nonleaf *nonleaf = static_cast<Nonleaf *>(node);
      for (int i = 0; i < nonleaf->size; ++i)
        traverse(nonleaf->children[i]);
      delete nonleaf;
    };
    traverse(root_);
  }

  void insert(const T &key) override {
    Leaf *leaf = search_leaf(key);
    Node *node = leaf;
    int i = utils::lower_bound(leaf->keys, leaf->size, key);
    if (leaf->size < M) {
      insert_item(leaf, i, key);
      ++leaf->size;
    } else {
      Node *child = nullptr;
      while (node->size == M) {
        if (node == root_) {
          Nonleaf *new_root = new Nonleaf;
          insert_child(new_root, 0, root_);
          ++new_root->size;
          root_ = new_root;
        }
        if (node->is_leaf)
          child = split_leaf(static_cast<Leaf *>(node), i, key);
        else
          child = split_nonleaf(static_cast<Nonleaf *>(node), i + 1, child);
        i = node->index();
        update_key(node->parent, i);
        node = node->parent;
      }
      insert_child(static_cast<Nonleaf *>(node), ++i, child);
      ++node->size;
    }
    while (node != root_ && i == node->size - 1) {
      i = node->index();
      update_key(node->parent, i);
      node = node->parent;
    }
  }

  void remove(const T &key) override {
    Leaf *leaf = search_leaf(key);
    int i = utils::lower_bound(leaf->keys, leaf->size, key);
    if (i == leaf->size || leaf->keys[i] != key)
      return;
    delete_item(leaf, i--);
    --leaf->size;
    Node *node = leaf;
    while (node->size < M / 2) {
      if (node == root_) {
        if (!node->is_leaf && node->size == 1) {
          root_ = static_cast<Nonleaf *>(node)->children[0];
          delete node;
        }
        break;
      }
      Nonleaf *p = node->parent;
      i = node->index();
      update_key(p, i);
      node = p;
      if (rebalance_child(p, i))
        break;
    }
    while (node != root_ && i == node->size - 1) {
      i = node->index();
      update_key(node->parent, i);
      node = node->parent;
    }
  }

  bool contains(const T &key) const override {
    Leaf *leaf = search_leaf(key);
    int i = utils::lower_bound(leaf->keys, leaf->size, key);
    return i < leaf->size && leaf->keys[i] == key;
  }

  int height() const override {
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      int h = 0;
      if (!node->is_leaf) {
        Nonleaf *nonleaf = static_cast<Nonleaf *>(node);
        for (int i = 0; i < nonleaf->size; ++i)
          h = max(h, traverse(nonleaf->children[i]));
      }
      return h + 1;
    };
    return traverse(root_);
  }

  int size() const override {
    Leaf *leaf = head_;
    int s = 0;
    while (leaf) {
      s += leaf->size;
      leaf = leaf->next;
    }
    return s;
  }

  bool empty() const override { return root_->size == 0; }

  vector<T> values() const override {
    vector<T> values;
    Leaf *leaf = head_;
    while (leaf) {
      for (int i = 0; i < leaf->size; ++i)
        values.push_back(leaf->keys[i]);
      leaf = leaf->next;
    }
    return values;
  }

  void print(ostream &os, const string &indent = "") const override {
    int depth = -1;
    function<string()> prefix = [&]() {
      return indent + string(depth * 3, ' ') + "|- ";
    };
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      ++depth;
      if (node->is_leaf) {
        Leaf *leaf = static_cast<Leaf *>(node);
        for (int i = 0; i < leaf->size; ++i)
          os << prefix() << leaf->keys[i] << endl;
      } else {
        Nonleaf *nonleaf = static_cast<Nonleaf *>(node);
        os << prefix() << nonleaf->keys[0] << endl;
        traverse(nonleaf->children[0]);
        for (int i = 1; i < nonleaf->size; ++i) {
          os << prefix() << nonleaf->keys[i - 1] << '<' << nonleaf->keys[i]
             << endl;
          traverse(nonleaf->children[i]);
        }
      }
      --depth;
    };
    traverse(root_);
  }

  void print_csv(ostream &os, const string &indent = "") const override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node->is_leaf) {
        Leaf *leaf = static_cast<Leaf *>(node);
        os << indent << *leaf << endl;
        return;
      }
      Nonleaf *nonleaf = static_cast<Nonleaf *>(node);
      os << indent << *nonleaf << endl;
      for (int i = 0; i < nonleaf->size; ++i)
        traverse(nonleaf->children[i]);
    };
    traverse(root_);
  }

  bool check() const override {
    function<bool(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node != root_ && node->size < M / 2)
        return false;
      if (!node->is_leaf) {
        Nonleaf *nonleaf = static_cast<Nonleaf *>(node);
        for (int i = 0; i < nonleaf->size; ++i)
          if (nonleaf->keys[i] != nonleaf->children[i]->max_key() ||
              !traverse(nonleaf->children[i]))
            return false;
      }
      return true;
    };
    if (!root_->is_leaf && root_->size < 2)
      return false;
    return traverse(root_);
  }
};