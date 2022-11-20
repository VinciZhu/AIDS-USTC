#include <cstring>
#include <fstream>
#include <iostream>

#include "BiTree.hpp"
#define MAX_SIZE 100

using namespace std;

BiTree<char> tree;
const BTNode<char>* ptr;
char key[MAX_SIZE + 1], pre[MAX_SIZE * 4], temp;
int siz, val[MAX_SIZE], idx[MAX_SIZE];
bool quit_flag;
string code[MAX_SIZE];
ifstream input;
ofstream output;

void print_tree(ostream& _out) {
  static int depth;
  static Stack<int> stack;
  static const BTNode<char>* pre;
  static ostream* out;
  depth = 0;
  stack.clear();
  pre = nullptr;
  out = &_out;
  tree.traverse([](const BTNode<char>& _node, const void*) {
    if (pre) {
      if (&_node != pre->lchild && &_node != pre->rchild) depth = stack.pop();
      for (int i = 0; i < depth; ++i) {
        *out << "    ";
      }
      switch (_node.data) {
        case '@':
          break;
        case ' ':
          *out << "空格";
          break;
        default:
          *out << _node.data;
          break;
      }
      *out << "(" << ((&_node == pre->lchild) ? '0' : '1') << ')' << endl;
    } else
      *out << "根节点" << endl;
    ++depth;
    pre = &_node;
    if (_node.lchild && _node.rchild) stack.push(depth);
  });
}

bool check() {
  if (tree.empty()) {
    input.open("hfmtree.txt");
    if (!input.is_open()) {
      cout << "hfmtree.txt打开失败\n";
      return false;
    }
    input.getline(pre, MAX_SIZE * 4);
    input.close();
    siz = (strlen(pre) + 1) / 4;
    tree.createFromExtendedPre(pre, siz * 4 - 1, '#');
    tree.getLeafData(key, siz);
    tree.getHuffmanCode(code, siz);
    for (int i = 0; i < siz; ++i) {
      idx[key[i]] = i;
    }
  }
  return true;
}

int main() {
  cout << "哈夫曼解编码\n1.初始化(I)\n2.编码(E)\n3.译码(D)\n4.打印代码文件(P)"
          "\n5.打印Huffman树(T)\n6.退出(Q)\n";
  while (!quit_flag) {
    cin >> temp;
    switch (temp) {
      case 'I':
        // Initialization
        tree.clear();
        siz = 0;
        input.open("CharSet.txt");
        if (!input.is_open()) {
          cout << "CharSet.txt打开失败\n";
          break;
        }
        while (!input.eof()) {
          input.get(key[siz]);
          input >> val[siz];
          input.get();
          siz++;
        }
        input.close();
        tree.createHuffman(key, val, siz, '@');
        tree.getLeafData(key, siz);
        tree.getHuffmanCode(code, siz);
        for (int i = 0; i < siz; ++i) {
          idx[key[i]] = i;
        }
        tree.getExtendedPreSequence(pre, siz * 4 - 1, '#');
        pre[siz * 4 - 1] = 0;
        output.open("hfmtree.txt", ios::out);
        output << pre << endl;
        output.close();
        cout << "初始化完成，Huffman树已存入hfmtree.txt中\n";
        break;
      case 'E':
        // Encoding
        if (!check()) break;
        input.open("ToBeTran.txt");
        if (!input.is_open()) {
          cout << "ToBeTran.txt打开失败\n";
          break;
        }
        output.open("CodeFile.txt", ios::out);
        while (!input.get(temp).eof()) {
          output << code[idx[temp]];
        }
        output.close();
        input.close();
        cout << "编码完成，编码结果已存入CodeFile.txt中\n";
        break;
      case 'D':
        // Decoding
        if (!check()) break;
        ptr = tree.root();
        input.open("CodeFile.txt");
        if (!input.is_open()) {
          cout << "CodeFile.txt打开失败\n";
          break;
        }
        output.open("TextFile.txt", ios::out);
        while (!input.get(temp).eof()) {
          ptr = temp == '1' ? ptr->rchild : ptr->lchild;
          if (ptr->isLeaf()) {
            output << ptr->data;
            ptr = tree.root();
          }
        }
        output.close();
        input.close();
        cout << "解码完成，解码结果已存入TextFile.txt中\n";
        break;
      case 'P':
        // Print
        input.open("CodeFile.txt");
        if (!input.is_open()) {
          cout << "CodeFile.txt打开失败\n";
          break;
        }
        output.open("CodePrint.txt", ios::out);
        for (int i = 1; !input.get(temp).eof(); ++i) {
          output << temp;
          cout << temp;
          if (i % 50 == 0) {
            output << endl;
            cout << endl;
          }
        }
        cout << endl;
        output.close();
        input.close();
        cout << "编码结果打印完成，打印结果已存入CodePrint.txt中\n";
        break;
      case 'T':
        // TreePrinting
        if (!check()) break;
        print_tree(cout);
        output.open("TreePrint.txt", ios::out);
        print_tree(output);
        output.close();
        cout << "Huffman树打印完成，打印结果已存入TreePrint.txt中\n";
        break;
      case 'Q':
        quit_flag = true;
        cout << "已退出\n";
        break;
    }
  }
  return 0;
}