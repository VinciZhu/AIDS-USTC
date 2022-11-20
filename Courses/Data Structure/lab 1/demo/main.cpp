#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

#include "linklist.h"


void main(){
    LinkList L;
    ElemType e;
    int i;

    cout<<"1）初始化单链表L"<<endl;
	InitList_L(L);
	cout<<"输出单链表L："<<endl;
    ListTraverse_L(L);
    cout<<"2）顺序插入链表元素a,b,c,d,e:"<<endl;
    for (int i = 0; i < 5; i++)
        ListInsert_L(L, i, 'a'+i-1);
    cout<<"3）输出单链表L："<<endl;
    ListTraverse_L(L);
    cout<<"4）单链表L长度="<<ListLength_L(L)<<endl;
    cout<<"5）单链表L"<<(ListEmpty_L(L)?"空":"非空")<<endl;
    if(GetItem_L(L,3,e))
        cout<<"6)单链表L中第3个元素是："<<e<<endl;
    cout<<"7）元素'b'在单链表中位序是："<<LocateItem_L(L, 'b')<<endl;
    cout<<"8）在单链表L中第4位置插入'f'."<<endl;
    cout<<(ListInsert_L(L, 4, 'f')?"插入成功.":"插入失败.")<<endl;
    cout<<"插入后单链表L："<<endl;
    ListTraverse_L(L);
    cout<<"9）删除单链表L中第3个元素."<<endl;
    cout<<(ListDelete_L(L,3,e)?"删除成功.":"删除失败.")<<endl;
    cout<<"删除后单链表L："<<endl;
    ListTraverse_L(L);
    cout<<"10）销毁单链表L"<<endl;
    DestroyList_L(L);
	cout<<"输出单链表L："<<endl;
    ListTraverse_L(L);
}

