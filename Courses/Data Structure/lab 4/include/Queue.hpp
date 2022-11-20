#pragma once
#include <iostream>

#include "List.hpp"

using namespace std;

template <class DataType>
class Queue {
 private:
  ListNode<DataType>* rear;

 public:
  Queue();
  ~Queue();
  void enqueue(const DataType& _data);
  DataType dequeue();
  void clear();
  int size() const;
  bool empty() const;
  void traverse(void (*_callback)(const ListNode<DataType>&, const void*),
                const void* _param = nullptr);
};

template <class DataType>
Queue<DataType>::Queue() {
  rear = new ListNode<DataType>;
  rear->next = rear;
};

template <class DataType>
Queue<DataType>::~Queue() {
  clear();
  delete rear;
}

template <class DataType>
void Queue<DataType>::enqueue(const DataType& _data) {
  ListNode<DataType>* node = new ListNode<DataType>(_data);
  node->next = rear->next;
  rear = rear->next = node;
}

template <class DataType>
DataType Queue<DataType>::dequeue() {
  if (empty()) {
    cerr << ERROR;
    return DataType();
  }
  ListNode<DataType>* node = rear->next->next;
  DataType data = node->data;
  rear->next->next = node->next;
  if (rear == node) {
    rear = rear->next;
  }
  delete node;
  return data;
}

template <class DataType>
void Queue<DataType>::clear() {
  while (!empty()) dequeue();
}

template <class DataType>
int Queue<DataType>::size() const {
  int size = 0;
  ListNode<DataType>* p = rear;
  while ((p = p->next) != rear) ++size;
  return size;
}

template <class DataType>
bool Queue<DataType>::empty() const {
  return rear->next == rear;
}

template <class DataType>
void Queue<DataType>::traverse(void (*_callback)(const ListNode<DataType>&,
                                                 const void*),
                               const void* _param) {
  ListNode<DataType>* p = rear->next;
  while ((p = p->next) != rear->next) {
    _callback(p->data, _param);
  }
}