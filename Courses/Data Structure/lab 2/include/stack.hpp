#pragma once
#include <cstring>
#include <iostream>

#include "list.hpp"
#define STACK_MIN_SIZE 10
#define STACK_INC_SIZE 10
using namespace std;

T class Stack {
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
  bool isEmpty() const;
  bool isFull() const;
  int size() const;
  void traverse(void (*_callback)(DataType&, void*), void* _param);
};

T Stack<DataType>::Stack(int _size) {
  data = new DataType[_size];
  top_ = -1;
  size_ = _size;
  if (!data) {
    cerr << ERROR;
  }
}

T Stack<DataType>::~Stack() { delete[] data; }

T void Stack<DataType>::resize(int _size) {
  DataType* newData = new DataType[_size];
  if (!newData) {
    cerr << ERROR;
  }
  for (int i = 0; i <= top_; i++) newData[i] = data[i];
  size_ = _size;
  delete[] data;
  data = newData;
}

T void Stack<DataType>::push(const DataType _data) {
  if (isFull()) resize(size_ + STACK_INC_SIZE);
  data[++top_] = _data;
}

T DataType Stack<DataType>::pop() {
  DataType temp = top();
  top_--;
  return temp;
}

T void Stack<DataType>::clear() { top_ = -1; }

T DataType Stack<DataType>::top() const {
  if (isEmpty()) {
    cerr << ERROR;
  }
  return data[top_];
}

T bool Stack<DataType>::isEmpty() const { return top_ == -1; }

T bool Stack<DataType>::isFull() const { return top_ == size_ - 1; }

T int Stack<DataType>::size() const { return top_ + 1; }

T void Stack<DataType>::traverse(void (*_callback)(DataType&, void*),
                                 void* _param) {
  for (int i = 0; i <= top_; i++) {
    _callback(data[i], _param);
  }
}