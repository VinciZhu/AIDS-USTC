#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;  //
#define N 3 //停车场park
#define M 4 //通道line

//车子
typedef struct Car{
    int num;
    int time;
}Car;

//栈
typedef struct stack{
    Car *base;
    Car *top;
    int curlen;
}Park,Tmp;

Park park; //停车场(栈)
Tmp tmp; //临时让路道(栈)

//链队列结点:数据域为车子
typedef struct Qnode{
    Car car;
    struct Qnode *next;
}Qnode, *queuePtr;

//链队列
typedef struct queue{
    queuePtr front;
    queuePtr rear;
    int curlen;
}Line;

Line line; //通道(链队列)

//初始化停车场park(栈)
void Initpark(){
    park.base=new Car [N];
    park.top=park.base;
    park.curlen=0;
}

//初始化临时让路道tmp(栈)
void Inittmp(){
    tmp.base=new Car [N];
    tmp.top=tmp.base;
    tmp.curlen=0;
}

//初始化通道line(链队列)
void Initline(){
    line.front =line.rear=new Qnode;
    line.front->next=NULL;
    line.curlen=0;
}

//车子进停车场park(栈)
void Inpark(Car e){
    *(park.top)=e;
    park.top++;
    park.curlen++;
    cout<<"车辆"<<e.num<<"停放在停车场第"<<park.curlen<<"个位置."<<endl;
}

//车子进通道line(链队列)
void Inline(Car e){
    Qnode *s = new Qnode ;
    s->car=e;
    s->next=NULL;
    line.rear->next=s;
    line.rear=s;
    line.curlen++;
    cout<<"车辆"<<e.num<<"停放在通道第"<<line.curlen<<"个位置."<<endl;
}

//车子进去临时让路道tmp(栈)
void Intmp(Car e){
    *(tmp.top)=e;
    tmp.top++;
    tmp.curlen++;
}

//出栈操作
void Outstack(stack *s){
    s->top--;
    s->curlen--;
}

//通道line(链队列)的第一辆车即队头元素
Car Outline(){
    Qnode *firstqnode=line.front->next;
    Car firstcar=firstqnode->car;
    line.front->next=firstqnode->next;
    line.curlen--;
    return firstcar;
}

//车子出停车场park
void Outpark(Car e){
    int num=e.num;
    int outtime=e.time; //离开时间
    Car *c=park.top-1; //栈顶元素
    while(c->num!=num&&park.top>park.base){
        Intmp(*c); //栈顶元素(车子)进临时让路道
        Outstack(&park); //栈顶元素(车子)暂时弹出去
        c--;
    }
    if(park.top==park.base) {
        cout<<"停车场无此车."<<endl;
    }
    else{
        int spendtime=outtime-(c->time);
        cout<<"停留时间："<<spendtime<<endl;
        cout<<"收费："<<spendtime*2<<endl;
        Outstack(&park); //车子出停车场
    }

    //将所有临时让路道里的车子出tmp栈,并入park栈
    while(tmp.curlen>0){
        Outstack(&tmp);
        Inpark(*(tmp.top));
    }

    //让通道line里的队头元素(车子)进停车场park
    while(park.curlen<N&&line.curlen>0){
        Car linefirstcar=Outline();
        linefirstcar.time=e.time;
        Inpark(linefirstcar);
    }
}

void Dispark(){
    cout<<"停车场:"<<endl;
    Car *p=park.base;
    while(p!=park.top){
        cout<<"车辆"<<p->num<<"到达时间："<<p->time<<endl;
        p++;
    }
}
void Disline(){
    cout<<"通道:"<<endl;
    Qnode *p=line.front->next;
    while(p){
        cout<<"车辆"<<(p->car).num<<"到达时间："<<(p->car).time<<endl;
        p=p->next;
    }
}

int main (){
    Initpark();
    Inittmp();
    Initline();
    char a[5];
    cout<<"请输入操作： 车牌号： 时间："<<endl;
    while (cin >> a){
        if ( !strcmp (a,"A")){
            Car car;
            cin>>car.num>>car.time;
            if(park.curlen<N)
                Inpark(car);
            else if(line.curlen<M)
                Inline(car);
            else
                cout<<"不好意思,无空地!"<<endl;
        }
        else if (!strcmp (a,"D")){
            Car car;
            cin>>car.num>>car.time;
            Outpark(car);
        }
        else if (!strcmp (a,"P")){
            Dispark();
        }
        else if (!strcmp (a,"W")){
            Disline();
        }
        else if (!strcmp (a,"E")){
            break;
        }
    }
}