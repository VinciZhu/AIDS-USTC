#pragma once
#include <iostream>

#include "List.hpp"
#define STACK_MIN_SIZE 10
#define STACK_INC_SIZE 10

using namespace std;

template <class DataType>
class Stack {
 private:
  DataType* data;
  int top_;
  int size_;

 public:
  Stack(int _size = STACK_MIN_SIZE);
  ~Stack();
  void push(const DataType _data);
  DataType pop();
  void resize(int _size);
  void clear();
  DataType top() const;
  bool empty() const;
  bool full() const;
  int size() const;
  void traverse(void (*_callback)(const ListNode<DataType>&, const void*),
                const void* _param = nullptr);
};

template <class DataType>
Stack<DataType>::Stack(int _size) {
  data = new DataType[_size];
  top_ = -1;
  size_ = _size;
  if (!data) {
    cerr << ERROR;
  }
}

template <class DataType>
Stack<DataType>::~Stack() {
  delete[] data;
}

template <class DataType>
void Stack<DataType>::resize(int _size) {
  DataType* newData = new DataType[_size];
  if (!newData) {
    cerr << ERROR;
  }
  for (int i = 0; i <= top_; i++) newData[i] = data[i];
  size_ = _size;
  delete[] data;
  data = newData;
}

template <class DataType>
void Stack<DataType>::push(const DataType _data) {
  if (full()) resize(size_ + STACK_INC_SIZE);
  data[++top_] = _data;
}

template <class DataType>
DataType Stack<DataType>::pop() {
  DataType temp = top();
  top_--;
  return temp;
}

template <class DataType>
void Stack<DataType>::clear() {
  top_ = -1;
}

template <class DataType>
DataType Stack<DataType>::top() const {
  if (empty()) {
    cerr << ERROR;
  }
  return data[top_];
}

template <class DataType>
bool Stack<DataType>::empty() const {
  return top_ == -1;
}

template <class DataType>
bool Stack<DataType>::full() const {
  return top_ == size_ - 1;
}

template <class DataType>
int Stack<DataType>::size() const {
  return top_ + 1;
}

template <class DataType>
void Stack<DataType>::traverse(void (*_callback)(const ListNode<DataType>&,
                                                 const void*),
                               const void* _param) {
  for (int i = 0; i <= top_; i++) {
    _callback(data[i], _param);
  }
}