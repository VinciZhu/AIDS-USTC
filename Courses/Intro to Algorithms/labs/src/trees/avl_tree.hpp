#pragma once
#include "binary_search_tree.hpp"

template <typename T> struct AVLTreeNode {
  T value;
  AVLTreeNode *left = nullptr;
  AVLTreeNode *right = nullptr;
  AVLTreeNode *parent = nullptr;
  int height = 0;
  AVLTreeNode(const T &value) : value(value) {}
  friend ostream &operator<<(ostream &os, const AVLTreeNode &node) {
    os << &node << ',' << node.value << ',' << node.left << ',' << node.right;
    return os;
  }
};

template <typename T>
class AVLTree : public BinarySearchTreeBase<T, AVLTreeNode> {
  using Node = AVLTreeNode<T>;
  using Base = BinarySearchTreeBase<T, AVLTreeNode>;

protected:
  int height(Node *node) const { return node == nullptr ? -1 : node->height; }

  void update_height(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));
  }

  int balance_factor(Node *node) const {
    return height(node->left) - height(node->right);
  }

  void rotate_left(Node *node) {
    Node *right = node->right;
    Base::transplant(node, right);
    Base::set_right(node, right->left);
    Base::set_left(right, node);
    update_height(node);
    update_height(right);
  }

  void rotate_right(Node *node) {
    Node *left = node->left;
    Base::transplant(node, left);
    Base::set_left(node, left->right);
    Base::set_right(left, node);
    update_height(node);
    update_height(left);
  }

  void rebalance(Node *node) {
    update_height(node);
    if (balance_factor(node) == 2) {
      if (balance_factor(node->left) < 0)
        rotate_left(node->left);
      rotate_right(node);
    } else if (balance_factor(node) == -2) {
      if (balance_factor(node->right) > 0)
        rotate_right(node->right);
      rotate_left(node);
    }
  }

  void insert_node(Node *node) override {
    Node *p = Base::search_parent(node->value);
    Base::set_child(p, node);
    while (p != nullptr) {
      rebalance(p);
      p = p->parent;
    }
  }

  void delete_node(Node *node) override {
    // relp: node to replace with
    // fix: node to rebalance
    Node *repl, *fix = node->parent;
    if (node->left == nullptr)
      repl = node->right;
    else if (node->right == nullptr)
      repl = node->left;
    else {
      fix = repl = Base::minimum(node->right);
      if (repl != node->right) {
        fix = repl->parent;
        Base::set_left(repl->parent, repl->right);
        Base::set_right(repl, node->right);
      }
      Base::set_left(repl, node->left);
    }
    Base::transplant(node, repl);
    delete node;
    while (fix != nullptr) {
      rebalance(fix);
      fix = fix->parent;
    }
  }

public:
  bool check() const override {
    // check if the tree is balanced
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return 0;
      int left = traverse(node->left);
      int right = traverse(node->right);
      if (left == -1 || right == -1 || abs(left - right) > 1)
        return -1;
      return 1 + max(left, right);
    };
    return traverse(Base::root_) != -1;
  }
};