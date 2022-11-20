#pragma once
#include <iostream>

#define inf 0xffff

enum Status { ERROR, OK };

using namespace std;

template <class DataType>
struct ListNode {
  ListNode* next;
  DataType data;
  ListNode(const DataType& _data = DataType()) : data(_data){};
};

template <class DataType>
class List {
 private:
  ListNode<DataType>* rear;

 public:
  List();
  ~List();
  void push_back(const DataType& _data);
  void push_front(const DataType& _data);
  DataType pop_back();
  DataType pop_front();
  void clear();
  int size() const;
  bool empty() const;
  void traverse(void (*_callback)(const ListNode<DataType>&, const void*),
                const void* _param = nullptr);
};

template <class DataType>
List<DataType>::List() {
  rear = new ListNode<DataType>;
  rear->next = rear;
};

template <class DataType>
List<DataType>::~List() {
  clear();
  delete rear;
}

template <class DataType>
void List<DataType>::push_back(const DataType& _data) {
  ListNode<DataType>* node = new ListNode<DataType>(_data);
  node->next = rear->next;
  rear = rear->next = node;
}

template <class DataType>
void List<DataType>::push_front(const DataType& _data) {
  ListNode<DataType>* node = new ListNode<DataType>(_data);
  if (empty()) {
    node->next = rear;
    rear = rear->next = node;
  } else {
    node->next = rear->next->next;
    rear->next->next = node;
  }
}

template <class DataType>
DataType List<DataType>::pop_back() {
  if (empty()) {
    cerr << ERROR;
    return DataType();
  }
  ListNode<DataType>* node = rear->next;
  while (node->next != rear) node = node->next;
  DataType data = rear->data;
  node->next = rear->next;
  delete rear;
  rear = node;
  return data;
}

template <class DataType>
DataType List<DataType>::pop_front() {
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
void List<DataType>::clear() {
  while (!empty()) pop_front();
}

template <class DataType>
int List<DataType>::size() const {
  int size = 0;
  ListNode<DataType>* p = rear;
  while ((p = p->next) != rear) ++size;
  return size;
}

template <class DataType>
bool List<DataType>::empty() const {
  return rear->next == rear;
}

template <class DataType>
void List<DataType>::traverse(void (*_callback)(const ListNode<DataType>&,
                                                const void*),
                              const void* _param) {
  ListNode<DataType>* p = rear->next;
  while ((p = p->next) != rear->next) {
    _callback(p->data, _param);
  }
}