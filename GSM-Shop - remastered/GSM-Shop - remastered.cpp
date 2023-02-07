// GSM Shop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <map>
#include "Phone.h"
#include "PhoneShop.h"
#include "Interface.h"
#include <fstream>

using namespace std;

int main()
{
    Interface myInterface;
    myInterface.AddPhone(Phone("Samsung", "A01", "SFF", "1990", "2.0", "50.00"));
    myInterface.AddPhone(Phone("Samsung", "A51", "SFF", "2020", "6.0", "2000.00"));
    myInterface.AddPhone(Phone("Samsung", "S2", "SFF", "2018", "6.0", "3000.00"));
    myInterface.AddPhone(Phone("Samsung", "A03", "SFF", "1990", "2.0", "50.00"));
    myInterface.AddPhone(Phone("Huwawie", "2", "FFS", "1800", "5.0", "2000.00"));
    myInterface.AddPhone(Phone("Huwawie", "65M", "FFS", "1800", "4.0", "2000.00"));
    myInterface.AddPhone(Phone("Samsung", "S6", "SFF", "2018", "12.0", "8000.00"));

    myInterface.Start();        

}