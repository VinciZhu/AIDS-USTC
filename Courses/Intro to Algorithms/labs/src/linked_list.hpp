#pragma once
#include <cstddef>

template <typename T> class LinkedList;
template <typename T> void insertion_sort(LinkedList<T> &list);

template <typename T> class LinkedList {
private:
  struct Node {
    T value;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(T value) : value(value) {}
  };
  Node *head_;
  Node *tail_;
  size_t size_;

public:
  class Iterator {
  private:
    Node *node;

  public:
    Iterator(Node *node) : node(node) {}
    bool operator!=(const Iterator &other) { return node != other.node; }
    void operator++() { node = node->next; }
    void operator--() { node = node->prev; }
    T &operator*() { return node->value; }
  };
  Iterator begin() { return Iterator(head_); }
  Iterator end() { return Iterator(nullptr); }

  LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
  LinkedList(const LinkedList &other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (T value : other)
      push_back(value);
  }
  LinkedList(LinkedList &&other)
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      clear();
      for (T value : other)
        push_back(value);
    }
    return *this;
  }
  LinkedList &operator=(LinkedList &&other) {
    if (this != &other) {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }
  ~LinkedList() { clear(); }
  void push_back(T value) {
    Node *node = new Node(value);
    if (tail_) {
      tail_->next = node;
      node->prev = tail_;
      tail_ = node;
    } else {
      head_ = tail_ = node;
    }
    size_++;
  }
  void push_front(T value) {
    Node *node = new Node(value);
    if (head_) {
      head_->prev = node;
      node->next = head_;
      head_ = node;
    } else {
      head_ = tail_ = node;
    }
    size_++;
  }
  void pop_back() {
    if (tail_) {
      Node *node = tail_;
      tail_ = tail_->prev;
      if (tail_)
        tail_->next = nullptr;
      else
        head_ = nullptr;
      delete node;
      size_--;
    }
  }
  void pop_front() {
    if (head_) {
      Node *node = head_;
      head_ = head_->next;
      if (head_)
        head_->prev = nullptr;
      else
        tail_ = nullptr;
      delete node;
      size_--;
    }
  }
  void clear() {
    while (head_)
      pop_front();
  }
  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  friend void insertion_sort<T>(LinkedList<T> &list);
};

template <typename T> void insertion_sort(LinkedList<T> &list) {
  for (auto p = list.head_; p; p = p->next) {
    auto key = p->value;
    auto q = p;
    while (q->prev && q->prev->value > key)
      q = q->prev;
    if (q != p) {
      p->prev->next = p->next;
      if (p->next)
        p->next->prev = p->prev;
      else
        list.tail_ = p->prev;
      p->next = q;
      p->prev = q->prev;
      if (q->prev)
        q->prev->next = p;
      else
        list.head_ = p;
      q->prev = p;
    }
  }
}