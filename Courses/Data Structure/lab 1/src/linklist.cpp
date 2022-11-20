#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

#include <cstring>

#include "linklist.h"

void InitList_L(LinkList &L) { L = NULL; };

void DestroyList_L(LinkList &L) {
  LNode *p;
  while (L) {
    p = L;
    L = L->next;
    delete p;
  }
};

bool ListEmpty_L(LinkList L) { return (L == NULL); };

int ListLength_L(LinkList L) {
  LNode *p = L;
  int k = 0;
  while (p) {
    p = p->next;
    k++;
  }
  //
  return k;
};

int LocateItem_L(LinkList L, ElemType e) {
  int j = 1;
  LNode *p = L;
  while (p && p->data != e) {
    p = p->next;
    j++;
  }
  if (p)
    return j;
  else
    return 0;
};

bool GetItem_L(LinkList L, int i, ElemType &e) {
  int j = 1;
  LNode *p = L;
  if (i < 1) {
    cout << "i值非法！" << endl;
    return false;
  }
  while (j < i && p) {
    j++;
    p = p->next;
  }
  if (p) {
    e = p->data;
    return true;
  } else
    return false;
};

bool ListInsert_L(LinkList &L, int i, ElemType e) {
  int j = 1;
  LNode *p = L, *s;
  if (i < 1) {
    cout << "i值非法！" << endl;
    return false;
  }
  while (j < i - 1 && p) {
    p = p->next;
    j++;
  }
  if (!p && i != 1) {
    cout << "未找到i-1节点" << endl;
    return false;
  }
  s = new LNode;
  s->data = e;
  //   if (i = 1) {
  if (i == 1) {
    s->next = L;
    L = s;
  } else {
    s->next = p->next;
    p->next = s;
  }
  return true;
};

bool ListDelete_L(LinkList &L, int i, ElemType &e) {
  int j = 1;
  LNode *p = L, *q;
  if (i < 1) {
    cout << "i值非法！" << endl;
    return false;
  }
  while (j < i - 1 && p) {
    p = p->next;
    j++;
  }
  if (!p || !(p->next)) {
    cout << "未找到i-1/i结点！" << endl;
    return false;
  }
  if (i == 1) {
    q = L;
    L = L->next;
    e = q->data;
  } else {
    q = p->next;
    p->next = q->next;
    e = q->data;
  }
  delete q;
  return true;
};

void ListTraverse_L(LinkList L) {
  LNode *p = L;
  while (p) {
    cout << p->data << ' ';
    p = p->next;
  }
  cout << endl;
};
