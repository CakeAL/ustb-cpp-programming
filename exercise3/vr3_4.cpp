//
// Created by cakeal on 2023/4/21.
//
#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

class MyStack{
private:
    int m_array[10]{};
    int m_size{};
public:
    MyStack() = default;
    bool push(int num);
    bool pop();
    void print();
};

bool MyStack::push(int num) {
    if(m_size == 10) return false;
    m_size++;
    m_array[m_size-1] = num;
    return true;
}

bool MyStack::pop() {
    if(m_size == 0) return false;
    m_size--;
    return true;
}

void MyStack::print() {
    cout << "( ";
    for(int i = 0; i < m_size; i++){
        cout << m_array[i] << " ";
    }
    cout << ")" << endl;
}

int main(){
    MyStack myStack = *new MyStack();
    char cmd;
    int num;
    while(cin >> cmd){
        switch (cmd) {
            case 'i':
                cin >> num;
                myStack.push(num);
                break;
            case 'o':
                if(!myStack.pop()){
                    cout << "Can not pop empty stack"<< endl;
                    return 0;
                }
                break;
            case 's':
                myStack.print();
                return 0;
            default:
                return 0;
        }
    }
    return 0;
}