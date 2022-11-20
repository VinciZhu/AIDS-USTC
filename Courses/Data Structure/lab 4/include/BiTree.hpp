#pragma once
#include <algorithm>
#include <iostream>

#include "Queue.hpp"
#include "Stack.hpp"

template <class DataType>
struct BTNode {
  BTNode* lchild;
  BTNode* rchild;
  DataType data;
  BTNode(const DataType& _data = DataType(), BTNode* _lchild = nullptr,
         BTNode* _rchild = nullptr)
      : data(_data), lchild(_lchild), rchild(_rchild){};
  bool isLeaf() const { return lchild == nullptr && rchild == nullptr; }
};

enum BTTraverseOrder { preOrder, inOrder, postOrder, layerOrder };

template <class DataType>
class BiTree {
 private:
  BTNode<DataType>* root_;

 public:
  BiTree();
  ~BiTree();
  void createFromExtendedPre(const DataType _pre[], int _size,
                             const DataType& _fill = DataType());
  void createFromPreIn(const DataType _pre[], const DataType _in[], int _size);
  void createFromPostIn(const DataType _post[], const DataType _in[],
                        int _size);
  void createHuffman(const DataType _data[], const int _weight[], int _size,
                     const DataType& _fill = DataType());
  void extend(const DataType& _fill = DataType());
  void clear();
  const BTNode<DataType>* root() const;
  const BTNode<DataType>* find(const DataType& _data) const;
  const BTNode<DataType>* lowestCommonAncestor(
      const BTNode<DataType>* _n1, const BTNode<DataType>* _n2) const;
  int size() const;
  int height() const;
  bool empty() const;
  bool complete() const;
  bool full() const;
  void traverse(void (*_callback)(const BTNode<DataType>&, const void*),
                const void* _param = nullptr,
                BTTraverseOrder _order = preOrder) const;
  void preOrderTraverse(void (*_callback)(const BTNode<DataType>&, const void*),
                        const void* _param = nullptr) const;
  void inOrderTraverse(void (*_callback)(const BTNode<DataType>&, const void*),
                       const void* _param = nullptr) const;
  void postOrderTraverse(void (*_callback)(const BTNode<DataType>&,
                                           const void*),
                         const void* _param = nullptr) const;
  void layerOrderTraverse(void (*_callback)(const BTNode<DataType>&,
                                            const void*),
                          const void* _param = nullptr) const;
  void getSequence(DataType _data[], int _size,
                   BTTraverseOrder _order = preOrder) const;
  void getExtendedPreSequence(DataType _data[], int _size,
                              const DataType& _fill = DataType()) const;
  void getLeafData(DataType _data[], int _size) const;
  void getHuffmanCode(string _code[], int _size) const;
};

template <class DataType>
BiTree<DataType>::BiTree(){};

template <class DataType>
BiTree<DataType>::~BiTree() {
  clear();
}

template <class DataType>
void BiTree<DataType>::createFromExtendedPre(const DataType _pre[], int _size,
                                             const DataType& _fill) {
  Stack<BTNode<DataType>*> stack;
  for (int i = _size - 1; i >= 0; --i) {
    if (_pre[i] == _fill)
      stack.push(nullptr);
    else
      stack.push(new BTNode<DataType>(_pre[i], stack.pop(), stack.pop()));
  }
  root_ = stack.pop();
}

template <class DataType>
void BiTree<DataType>::createFromPreIn(const DataType _pre[],
                                       const DataType _in[], int _size) {
  root_ = new BTNode<DataType>;
  root_->data = _pre[0];
  Stack<BTNode<DataType>*> stack;
  stack.push(root_);
  BTNode<DataType>*node, *parent = nullptr;
  for (int i = 1, j = 0; i < _size; ++i) {
    node = new BTNode<DataType>;
    node->data = _pre[i];
    parent = nullptr;
    while (!stack.empty() && stack.top()->data == _in[j]) {
      parent = stack.pop();
      ++j;
    }
    if (parent) {
      parent->rchild = node;
      stack.push(node);
    } else {
      stack.top()->lchild = node;
      stack.push(node);
    }
  }
}

template <class DataType>
void BiTree<DataType>::createFromPostIn(const DataType _post[],
                                        const DataType _in[], int _size) {
  root_ = new BTNode<DataType>;
  root_->data = _post[_size - 1];
  Stack<BTNode<DataType>*> stack;
  stack.push(root_);
  BTNode<DataType>*node, *parent = nullptr;
  for (int i = _size - 2, j = _size - 1; i >= 0; --i) {
    node = new BTNode<DataType>;
    node->data = _post[i];
    parent = nullptr;
    while (!stack.empty() && stack.top()->data == _in[j]) {
      parent = stack.pop();
      --j;
    }
    if (parent) {
      parent->lchild = node;
      stack.push(node);
    } else {
      stack.top()->rchild = node;
      stack.push(node);
    }
  }
}

template <class DataType>
void BiTree<DataType>::createHuffman(const DataType _data[],
                                     const int _weight[], int _size,
                                     const DataType& _fill) {
  struct weightedNode {
    BTNode<DataType>* ptr;
    int weight;
  } node[_size * 2 - 1];
  for (int i = 0; i < _size; ++i) {
    node[i].ptr = new BTNode<DataType>(_data[i]);
    node[i].weight = _weight[i];
  }
  for (int i = 0; i < _size - 1; ++i) {
    stable_sort(node, node + _size + i,
                [](const weightedNode& _n1, const weightedNode& _n2) {
                  return _n1.weight < _n2.weight;
                });
    node[_size + i].ptr = new BTNode<DataType>(_fill);
    node[_size + i].ptr->lchild = node[0].ptr;
    node[_size + i].ptr->rchild = node[1].ptr;
    node[_size + i].weight = node[0].weight + node[1].weight;
    node[0].weight = node[1].weight = inf;
  }
  root_ = node[_size * 2 - 2].ptr;
}

template <class DataType>
void BiTree<DataType>::extend(const DataType& _fill) {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    BTNode<DataType>* node = nullptr;
    stack.push(root_);
    while (!stack.empty()) {
      node = stack.pop();
      do {
        if (!node->rchild)
          node->rchild = new BTNode<DataType>(_fill);
        else
          stack.push(node->rchild);
        if (!node->lchild) {
          node->lchild = new BTNode<DataType>(_fill);
          node = nullptr;
        } else
          node = node->lchild;
      } while (node);
    }
  }
}

template <class DataType>
void BiTree<DataType>::clear() {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    stack.push(root_);
    BTNode<DataType>* node;
    while (!stack.empty()) {
      node = stack.pop();
      if (node->lchild) stack.push(node->lchild);
      if (node->rchild) stack.push(node->rchild);
      delete node;
    }
    root_ = nullptr;
  }
}

template <class DataType>
const BTNode<DataType>* BiTree<DataType>::root() const {
  return root_;
}

template <class DataType>
const BTNode<DataType>* BiTree<DataType>::find(const DataType& _data) const {
  static const BTNode<DataType>* node;
  node = nullptr;
  traverse(
      [](const BTNode<DataType>& _node, const void* _data) {
        if (*(const DataType*)_data == _node.data) {
          node = &_node;
        }
      },
      &_data);
  return node;
}

template <class DataType>
const BTNode<DataType>* BiTree<DataType>::lowestCommonAncestor(
    const BTNode<DataType>* _n1, const BTNode<DataType>* _n2) const {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    const BTNode<DataType>*node = root_, *pre = root_, *a1 = _n1, *a2 = _n2;
    stack.push(root_);
    while (!stack.empty()) {
      node = stack.top();
      if (!node->lchild && !node->rchild || pre == node->rchild ||
          pre == node->lchild) {
        pre = stack.pop();
        if (node->lchild == a1 || node->rchild == a1) a1 = node;
        if (node->lchild == a2 || node->rchild == a2) a2 = node;
        if (a1 == a2) return a1;
      } else {
        if (node->rchild) stack.push(node->rchild);
        if (node->lchild) stack.push(node->lchild);
      }
    }
  }
  return nullptr;
}

template <class DataType>
int BiTree<DataType>::size() const {
  static int size;
  size = 0;
  traverse([](const BTNode<DataType>&, const void*) { ++size; });
  return size;
}

template <class DataType>
int BiTree<DataType>::height() const {
  static int height;
  static Stack<int> stack;
  height = 0;
  stack.clear();
  postOrderTraverse([](const BTNode<DataType>& _node, const void*) {
    stack.push(height = 1 + max(_node.lchild ? stack.pop() : 0,
                                _node.rchild ? stack.pop() : 0));
  });
  return height;
}

template <class DataType>
bool BiTree<DataType>::empty() const {
  return root_ == nullptr;
}

template <class DataType>
bool BiTree<DataType>::complete() const {
  if (!empty()) {
    Queue<BTNode<DataType>*> queue;
    BTNode<DataType>* node = nullptr;
    bool flag = false;
    queue.enqueue(root_);
    while (!queue.empty()) {
      node = queue.dequeue();
      if (node->lchild) {
        if (flag) return false;
        queue.enqueue(node->lchild);
      }
      if (node->rchild)
        queue.enqueue(node->rchild);
      else
        flag = true;
    }
  }
  return true;
}

template <class DataType>
bool BiTree<DataType>::full() const {
  return size() == (1 << height()) - 1;
}

template <class DataType>
void BiTree<DataType>::traverse(void (*_callback)(const BTNode<DataType>&,
                                                  const void*),
                                const void* _param,
                                BTTraverseOrder _order) const {
  switch (_order) {
    case preOrder:
      preOrderTraverse(_callback, _param);
      break;
    case inOrder:
      inOrderTraverse(_callback, _param);
      break;
    case postOrder:
      postOrderTraverse(_callback, _param);
      break;
    case layerOrder:
      layerOrderTraverse(_callback, _param);
      break;
    default:
      break;
  }
}

template <class DataType>
void BiTree<DataType>::preOrderTraverse(
    void (*_callback)(const BTNode<DataType>&, const void*),
    const void* _param) const {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    BTNode<DataType>* node = nullptr;
    stack.push(root_);
    while (!stack.empty()) {
      node = stack.pop();
      do {
        _callback(*node, _param);
        if (node->rchild) stack.push(node->rchild);
        node = node->lchild;
      } while (node);
    }
  }
}

template <class DataType>
void BiTree<DataType>::inOrderTraverse(
    void (*_callback)(const BTNode<DataType>&, const void*),
    const void* _param) const {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    BTNode<DataType>* node = root_;
    while (!stack.empty() || node) {
      while (node) {
        stack.push(node);
        node = node->lchild;
      };
      node = stack.pop();
      _callback(*node, _param);
      node = node->rchild;
    }
  }
}

template <class DataType>
void BiTree<DataType>::postOrderTraverse(
    void (*_callback)(const BTNode<DataType>&, const void*),
    const void* _param) const {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    BTNode<DataType>*node = root_, *pre = root_;
    stack.push(root_);
    while (!stack.empty()) {
      node = stack.top();
      if (!node->lchild && !node->rchild || pre == node->rchild ||
          pre == node->lchild) {
        pre = stack.pop();
        _callback(*node, _param);
      } else {
        if (node->rchild) stack.push(node->rchild);
        if (node->lchild) stack.push(node->lchild);
      }
    }
  }
}

template <class DataType>
void BiTree<DataType>::layerOrderTraverse(
    void (*_callback)(const BTNode<DataType>&, const void*),
    const void* _param) const {
  if (!empty()) {
    Queue<BTNode<DataType>*> queue;
    BTNode<DataType>* node = nullptr;
    queue.enqueue(root_);
    while (!queue.empty()) {
      node = queue.dequeue();
      _callback(*node, _param);
      if (node->lchild) queue.enqueue(node->lchild);
      if (node->rchild) queue.enqueue(node->rchild);
    }
  }
}

template <class DataType>
void BiTree<DataType>::getSequence(DataType _data[], int _size,
                                   BTTraverseOrder _order) const {
  static int size;
  static DataType* ptr;
  size = _size;
  ptr = _data;
  traverse(
      [](const BTNode<DataType>& _node, const void*) {
        if (size--) *ptr++ = _node.data;
      },
      nullptr, _order);
}

template <class DataType>
void BiTree<DataType>::getExtendedPreSequence(DataType _data[], int _size,
                                              const DataType& _fill) const {
  if (!empty()) {
    Stack<BTNode<DataType>*> stack;
    BTNode<DataType>* node;
    stack.clear();
    node = nullptr;
    stack.push(root_);
    while (!stack.empty()) {
      node = stack.pop();
      if (!node) {
        if (_size--) *_data++ = _fill;
      } else {
        do {
          if (_size--) *_data++ = node->data;
          stack.push(node->rchild);
          node = node->lchild;
        } while (node);
        if (_size--) *_data++ = _fill;
      }
    }
  }
}

template <class DataType>
void BiTree<DataType>::getLeafData(DataType _data[], int _size) const {
  static int size;
  static DataType* ptr;
  size = _size;
  ptr = _data;
  traverse([](const BTNode<DataType>& _node, const void*) {
    if (_node.isLeaf() && size--) *ptr++ = _node.data;
  });
}

template <class DataType>
void BiTree<DataType>::getHuffmanCode(string _code[], int _size) const {
  static int depth, size;
  static Stack<int> stack;
  static const BTNode<char>* pre;
  static string* ptr;
  static string code;
  depth = -1;
  size = _size;
  stack.clear();
  pre = nullptr;
  ptr = _code;
  code = "";
  traverse([](const BTNode<DataType>& _node, const void*) {
    if (pre)
      if (&_node == pre->lchild)
        code += '0';
      else {
        if (&_node != pre->rchild) code.resize(depth = stack.pop());
        code += '1';
      }
    ++depth;
    pre = &_node;
    if (_node.lchild && _node.rchild) stack.push(depth);
    if (_node.isLeaf() && size--) *ptr++ = code;
  });
}