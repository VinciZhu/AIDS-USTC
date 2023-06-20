#pragma once
#include "binary_search_tree.hpp"

enum class RedBlackTreeColor : bool { Red, Black };

template <typename T> struct RedBlackTreeNode {
  using enum RedBlackTreeColor;
  T value;
  RedBlackTreeNode *left = nullptr;
  RedBlackTreeNode *right = nullptr;
  RedBlackTreeNode *parent = nullptr;
  RedBlackTreeColor color = Red;
  RedBlackTreeNode(const T &value) : value(value) {}
  friend ostream &operator<<(ostream &os, const RedBlackTreeNode &node) {
    os << &node << ',' << node.value << ',' << node.left << ',' << node.right
       << ',' << (node.color == Red ? 'R' : 'B');
    return os;
  }
};

template <typename T>
class RedBlackTree : public BinarySearchTreeBase<T, RedBlackTreeNode> {
  using Node = RedBlackTreeNode<T>;
  using Base = BinarySearchTreeBase<T, RedBlackTreeNode>;
  using enum RedBlackTreeColor;

protected:
  void rotate_left(Node *node) {
    Node *right = node->right;
    Base::transplant(node, right);
    Base::set_right(node, right->left);
    Base::set_left(right, node);
  }

  void rotate_right(Node *node) {
    Node *left = node->left;
    Base::transplant(node, left);
    Base::set_left(node, left->right);
    Base::set_right(left, node);
  }

  bool black(Node *node) const {
    return node == nullptr || node->color == Black;
  }

  bool red(Node *node) const { return !black(node); }

  void insert_node(Node *node) override {
    Base::insert_node(node);
    insert_fixup(node);
  }

  void insert_fixup(Node *node) {
    Node *p = node->parent;
    while (red(p)) {
      Node *gp = p->parent;

      // p is left child
      if (p == gp->left) {
        Node *u = gp->right;
        if (red(u)) {
          // case 1 -> ?
          p->color = u->color = Black;
          gp->color = Red;
          node = gp;
          p = gp->parent;
          continue;
        }
        if (node == p->right) {
          // case 2 -> 3
          rotate_left(p);
          p = node;
        }
        // case 3
        p->color = Black;
        gp->color = Red;
        rotate_right(gp);
        break;
      }

      // p is right child
      Node *u = gp->left;
      if (red(u)) {
        // case 4 -> ?
        p->color = u->color = Black;
        gp->color = Red;
        node = gp;
        p = gp->parent;
        continue;
      }
      // case 5 -> 6
      if (node == p->left) {
        rotate_right(p);
        p = node;
      }
      // case 6
      p->color = Black;
      gp->color = Red;
      rotate_left(gp);
      break;
    }
    Base::root_->color = Black;
  }

  void delete_node(Node *node) override {
    // relp: node to replace with
    // fix: node to fix up from
    // fix_p: parent of `fix`
    Node *repl, *fix, *fix_p = node->parent;
    if (node->left == nullptr)
      fix = repl = node->right;
    else if (node->right == nullptr)
      fix = repl = node->left;
    else {
      fix_p = repl = Base::minimum(node->right);
      fix = repl->right;
      if (repl != node->right) {
        fix_p = repl->parent;
        Base::set_left(repl->parent, repl->right);
        Base::set_right(repl, node->right);
      }
      Base::set_left(repl, node->left);
      swap(repl->color, node->color);
    }
    Base::transplant(node, repl);
    if (node->color == Black)
      delete_fixup(fix, fix_p);
    delete node;
  }

  void delete_fixup(Node *node, Node *p) {
    while (p != nullptr && black(node)) {

      // node is left child
      if (node == p->left) {
        Node *s = p->right;
        if (red(s)) {
          // case 1 -> 2, 3, 4
          s->color = Black;
          p->color = Red;
          rotate_left(p);
          s = p->right;
        }
        if (black(s->left) && black(s->right)) {
          // case 2 -> ?
          s->color = Red;
          node = p;
          p = p->parent;
          continue;
        }
        if (black(s->right)) {
          // case 3 -> 4
          s->left->color = Black;
          s->color = Red;
          rotate_right(s);
          s = p->right;
        }
        // case 4
        s->color = p->color;
        p->color = s->right->color = Black;
        rotate_left(p);
        break;
      }

      // node is right child
      Node *s = p->left;
      if (red(s)) {
        // case 5 -> 6, 7, 8
        s->color = Black;
        p->color = Red;
        rotate_right(p);
        s = p->left;
      }
      if (black(s->left) && black(s->right)) {
        // case 6 -> ?
        s->color = Red;
        node = p;
        p = p->parent;
        continue;
      }
      if (black(s->left)) {
        // case 7 -> 8
        s->right->color = Black;
        s->color = Red;
        rotate_left(s);
        s = p->left;
      }
      // case 8
      s->color = p->color;
      p->color = s->left->color = Black;
      rotate_right(p);
      break;
    }
    if (node != nullptr)
      node->color = Black;
  }

public:
  bool check() const override {
    if (Base::root_ == nullptr)
      return true;
    // property 2
    if (Base::root_->color != Black)
      return false;
    function<int(Node *)> traverse;
    traverse = [&](Node *node) {
      if (node == nullptr)
        return 1;
      // property 4
      if (node->color == Red && (red(node->left) || red(node->right)))
        return -1;
      int left = traverse(node->left);
      int right = traverse(node->right);
      // property 5
      if (left == -1 || right == -1 || left != right)
        return -1;
      return left + (node->color == Black);
    };
    return traverse(Base::root_) != -1;
  }
};