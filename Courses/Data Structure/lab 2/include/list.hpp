#pragma once
#define T template <typename DataType>
using namespace std;

enum Status { ERROR, OK };

T struct ListNode {
  DataType data;
  ListNode* next;
  ListNode();
  ListNode(DataType _data);
};

T class List {
 private:
  ListNode<DataType>* rear;

 public:
  List();
  ~List();
  void insert(const DataType& _data);
  void query(int _pos);
  DataType erase(int _pos);
  void clear();
  bool isEmpty();
};