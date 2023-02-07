#pragma once

#include <iostream>
#include <list>
#include <string>
#include <map>

using namespace std;

int idCounter = 0;

class Phone {
public:

    bool operator < (const Phone& p) const
    {
        return phoneName < p.phoneName;
    }

    friend bool operator == (const Phone& p1, const Phone& p2);


    Phone() {
        phoneName = "unknown";
        modelName = "unknown";
        formFactor = "unknown";
        yearOfIssue = 0;
        screenSizeInches = "0";
        price = 0;
        ID = idCounter;
        idCounter++;
    }

    Phone(string myphoneName, string mymodelName, string myformFactor, int myyearOfIssue, string myscreenSizeInches, float myprice)
    {
        phoneName = myphoneName;
        modelName = mymodelName;
        formFactor = myformFactor;
        yearOfIssue = myyearOfIssue;
        screenSizeInches = myscreenSizeInches;
        price = myprice;
        ID = idCounter;
        idCounter++;
    }

    int GetID() {
        return ID;
    }
    string GetPhoneName() {
        return phoneName;
    }
    string GetPhoneModel() {
        return modelName;
    }
    string GetFormFactor()
    {
        return formFactor;
    }
    int GetYearOfIssue() {
        return yearOfIssue;
    }

    string GetScreenSizeInches() {
        return screenSizeInches;
    }

    float GetPrice() {
        return price;
    }

    int ID;
    string phoneName;
    string modelName;
    string formFactor;
    int yearOfIssue;
    string screenSizeInches;
    float price;
};

bool operator== (const Phone& p1, const Phone& p2)
{
    if (p1.ID == p2.ID)
        return true;
    return false;
}

class FFComparator
{
public:
    bool operator()(const Phone& phone1, const Phone& phone2) {
        return phone1.formFactor < phone2.formFactor;
    }
};

class ScreemSizeComparator
{
public:
    bool operator()(const Phone& phone1, const Phone& phone2) {
        return phone1.screenSizeInches < phone2.screenSizeInches;
    }
};
