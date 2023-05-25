#include "bankusers.h"

BankUsers::BankUsers(string ID, string password): ID(ID), password(password)
{

}

string BankUsers::getID() const{
    return this->ID;
}

string BankUsers::getPassword() const{
    return this->password;
}
