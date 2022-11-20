#include <iostream>
#include <fstream>

#include "queue.hpp"
#include "stack.hpp"
using namespace std;
struct Car {
  string number;
  int time;
};
int n = 3, m = 4, p = 2;
Queue<Car> way;
Stack<Car> park(n), temp(n);
void arrive(const Car& car);
void depart(const Car& car);
void queryPark();
void queryWay();
void printQuery(Car& car, void* param);
int main() {
  ifstream input;
  input.open("input.txt");
  char cmd;
  Car car;
  cout << "请输入操作：\t车牌号：\t时间：" << endl;
  do {
    input >> cmd;
    switch (cmd) {
      case 'A':
        input >> car.number >> car.time;
        arrive(car);
        break;
      case 'D':
        input >> car.number >> car.time;
        depart(car);
        break;
      case 'P':
        queryPark();
        break;
      case 'W':
        queryWay();
        break;
      default:
        break;
    }
  } while (cmd != 'E');
  return 0;
}
void arrive(const Car& car) {
  if (park.isFull()) {
    way.enqueue(car);
    cout << "车辆" << car.number << "停放在通道第" << way.size() << "个位置。"
         << endl;
  } else {
    park.push(car);
    cout << "车辆" << car.number << "停放在停车场第" << park.size()
         << "个位置。" << endl;
  }
}
void depart(const Car& car) {
  while (car.number != park.top().number) {
    temp.push(park.pop());
  }
  cout << "停留时间：" << car.time - park.top().time << endl
       << "收费：" << p * (car.time - park.top().time) << endl;
  park.pop();
  while (!temp.isEmpty()) {
    park.push(temp.pop());
    cout << "车辆" << park.top().number << "停放在停车场第" << park.size()
         << "个位置。" << endl;
  }
  if(!way.isEmpty()){
    Car c = way.dequeue();
    c.time = car.time;
    park.push(c);
    cout << "车辆" << park.top().number << "停放在停车场第" << park.size()
         << "个位置。" << endl;
  }
}
void queryPark() {
  cout << "停车场：" << endl;
  park.traverse(printQuery, nullptr);
}
void queryWay() {
  cout << "通道：" << endl;
  way.traverse(printQuery, nullptr);
}
void printQuery(Car& car, void* param) {
  cout << "车辆" << car.number << "到达时间：" << car.time << endl;
}
