#ifndef BANKUSERS_H
#define BANKUSERS_H

#include "string"
using namespace std;

class BankUsers
{
private:
    string ID;
    string password;
public:
    BankUsers(string ID, string password);
    ~BankUsers() = default;
    //bool FindRepeatedUser(string ID); //找到重复的ID，如果找到则提示“重复的用户名”
    string getID() const;
    string getPassword() const;
};

#endif // BANKUSERS_H
