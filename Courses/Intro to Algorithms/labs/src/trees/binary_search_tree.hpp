#pragma once
#include "base.hpp"

template <typename T, template <typename> class N>
class BinarySearchTreeBase : public SearchTreeInterface<T> {
protected:
  using Node = N<T>;
  Node *root_ = nullptr;

  virtual void set_root(Node *node) {
    if (node != nullptr)
      node->parent = nullptr;
    root_ = node;
  }

  virtual void set_left(Node *node, Node *c) {
    if (c != nullptr)
      c->parent = node;
    node->left = c;
  }

  virtual void set_right(Node *node, Node *c) {
    if (c != nullptr)
      c->parent = node;
    node->right = c;
  }

  virtual void set_child(Node *node, Node *c) {
    assert(c != nullptr);
    if (node == nullptr)
      set_root(c);
    else if (c->value < node->value)
      set_left(node, c);
    else
      set_right(node, c);
  }

  virtual void transplant(Node *dest, Node *src) {
    if (dest->parent == nullptr)
      set_root(src);
    else if (dest == dest->parent->left)
      set_left(dest->parent, src);
    else
      set_right(dest->parent, src);
  }

  virtual Node *search_node(const T &value) const {
    Node *cur = root_;
    while (cur != nullptr && cur->value != value)
      cur = (value < cur->value) ? cur->left : cur->right;
    return cur;
  }

  virtual Node *search_parent(const T &value) const {
    Node *cur = root_, *p = nullptr;
    while (cur != nullptr) {
      p = cur;
      cur = (value < cur->value) ? cur->left : cur->right;
    }
    return p;
  }

  virtual void insert_node(Node *node) {
    set_child(search_parent(node->value), node);
  }

  virtual void delete_node(Node *node) {
    Node *repl;
    if (node->left == nullptr)
      repl = node->right;
    else if (node->right == nullptr)
      repl = node->left;
    else {
      repl = minimum(node->right);
      if (repl != node->right) {
        set_left(repl->parent, repl->right);
        set_right(repl, node->right);
      }
      set_left(repl, node->left);
    }
    transplant(node, repl);
    delete node;
  }

  virtual Node *minimum(Node *node) const {
    while (node->left != nullptr)
      node = node->left;
    return node;
  }

public:
  ~BinarySearchTreeBase() override { clear(); }

  void clear() override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return;
      traverse(node->left);
      traverse(node->right);
      delete node;
    };
    root_ = nullptr;
  }

  void insert(const T &value) override {
    Node *node = new Node(value);
    insert_node(node);
  }

  void remove(const T &value) override {
    Node *node = search_node(value);
    if (node != nullptr)
      delete_node(node);
  }

  bool contains(const T &value) const override {
    return search_node(value) != nullptr;
  }

  int height() const override {
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return -1;
      return 1 + max(traverse(node->left), traverse(node->right));
    };
    return traverse(root_);
  }

  int size() const override {
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return 0;
      return 1 + traverse(node->left) + traverse(node->right);
    };
    return traverse(root_);
  }

  bool empty() const override { return root_ == nullptr; }

  vector<T> values() const override {
    vector<T> values;
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return;
      traverse(node->left);
      values.push_back(node->value);
      traverse(node->right);
    };
    traverse(root_);
    return values;
  }

  void print(ostream &os = cout, const string& indent = "") const override {
    int depth = 0;
    function<string()> prefix = [&]() {
      return indent + string(depth * 3, ' ') + "|- ";
    };
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr) {
        os << prefix() << "nil" << endl;
        return;
      }
      os << prefix() << node->value << endl;
      ++depth;
      traverse(node->left);
      traverse(node->right);
      --depth;
    };
    traverse(root_);
  }

  void print_csv(ostream &os = cout, const string& indent = "") const override {
    function<void(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return;
      os << indent << *node << endl;
      traverse(node->left);
      traverse(node->right);
    };
    traverse(root_);
  }
};

template <typename T> struct BinarySearchTreeNode {
  T value;
  BinarySearchTreeNode *left = nullptr;
  BinarySearchTreeNode *right = nullptr;
  BinarySearchTreeNode *parent = nullptr;
  BinarySearchTreeNode(const T &value) : value(value) {}
  friend ostream &operator<<(ostream &os, const BinarySearchTreeNode &node) {
    os << &node << ',' << node.value << ',' << node.left << ',' << node.right;
    return os;
  }
};

template <typename T>
using BinarySearchTree = BinarySearchTreeBase<T, BinarySearchTreeNode>;