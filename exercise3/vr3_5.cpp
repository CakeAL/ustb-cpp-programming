//
// Created by cakeal on 2023/4/21.
//
#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

class PoweredDevice{
private:
    static int numOfDevices;
public:
    PoweredDevice(){
        numOfDevices++;
        cout << "A new PoweredDevice is constructed." << endl;
        cout << "There are " << numOfDevices << " PoweredDevices in total." << endl;
    };
    virtual void WhatAmI() = 0;
};

class Scanner : virtual public PoweredDevice{
private:
    static int numOfDevices;
public:
    Scanner(){
        numOfDevices++;
        cout << "A new Scanner is constructed." << endl;
        cout << "There are " << numOfDevices << " Scanner in total." << endl;
    };
    void WhatAmI() override {
        cout << "Scanner" << endl;
    }
};

class Printer : virtual public PoweredDevice{ //使用虚继承避免Copier类二义性
private:
    static int numOfDevices;
public:
    Printer(){
        numOfDevices++;
        cout << "A new Printer is constructed." << endl;
        cout << "There are " << numOfDevices << " Printer in total." << endl;
    };
    void WhatAmI() override {
        cout << "Printer" << endl;
    }
};

class Copier : public Scanner, public Printer{
private:
    static int numOfDevices;
public:
    Copier(){
        numOfDevices++;
        cout << "A new Copier is constructed." << endl;
        cout << "There are " << numOfDevices << " Copiers in total." << endl;
    };
    void WhatAmI() override {
        cout << "Copier" << endl;
    }
};

int PoweredDevice::numOfDevices = 0;
int Scanner::numOfDevices = 0;
int Printer::numOfDevices = 0;
int Copier::numOfDevices = 0;

int main(){
    char cmd;
    int numOfDevices = 0;
    PoweredDevice* devices[100];
    while(cin >> cmd){
        switch (cmd) {
            case 's':
                devices[numOfDevices++] = new Scanner();
                break;
            case 'p':
                devices[numOfDevices++] = new Printer();
                break;
            case 'c':
                devices[numOfDevices++] = new Copier();
                break;
            case 'e':
                cout << "The devices are:" << endl;
                for (int i = 0; i < numOfDevices; ++i) {
                    devices[i]->WhatAmI();
                }
                return 0;
            default:
                return 0;
        }
    }
    return 0;
}