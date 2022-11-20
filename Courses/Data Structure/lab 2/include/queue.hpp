#pragma once
#include <iostream>

#include "list.hpp"

using namespace std;

T class Queue {
 private:
  ListNode<DataType>* rear;

 public:
  Queue();
  ~Queue();
  void enqueue(const DataType& _data);
  DataType dequeue();
  void clear();
  int size() const;
  bool isEmpty() const;
  void traverse(void (*_callback)(DataType&, void*), void* _param);
};

T ListNode<DataType>::ListNode(){};

T ListNode<DataType>::ListNode(DataType _data) : data(_data){};

T Queue<DataType>::Queue() {
  rear = new ListNode<DataType>;
  rear->next = rear;
};

T Queue<DataType>::~Queue() {
  clear();
  delete rear;
}

T void Queue<DataType>::enqueue(const DataType& _data) {
  ListNode<DataType>* node = new ListNode<DataType>(_data);
  node->next = rear->next;
  rear = rear->next = node;
}

T DataType Queue<DataType>::dequeue() {
  if (isEmpty()) {
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

T void Queue<DataType>::clear() {
  while (!isEmpty()) dequeue();
}

T int Queue<DataType>::size() const {
  int size = 0;
  ListNode<DataType>* p = rear;
  while ((p = p->next) != rear) ++size;
  return size;
}

T bool Queue<DataType>::isEmpty() const { return rear->next == rear; }

T void Queue<DataType>::traverse(void (*_callback)(DataType&, void*),
                                 void* _param) {
  ListNode<DataType>* p = rear->next;
  while ((p = p->next) != rear->next) {
    _callback(p->data, _param);
  }
}