// GSM Shop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <map>
#include "Phone.h";

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

class PhoneShop {
private:
    list <Phone> phones;
    int brandNum = 0;

public:
    map <string, int> Brands;
    map<string, int> SizePopularity;

    void AddPhone()
    {
        string phoneName;
        string modelName;
        string formFactor;
        int yearOfIssue;
        string screenSizeInches;
        float price;
        getline(cin, phoneName);
        cout << "Type the name of the phone" << endl;
        getline(cin, phoneName);
        cout << "Type the name of the model" << endl;
        getline(cin, modelName);
        cout << "Type the form factor" << endl;
        getline(cin, formFactor);
        cout << "Type the year of issue" << endl;
        cin >> yearOfIssue;
        cout << "Type the screen size (in inches)" << endl;
        cin >> screenSizeInches;
        cout << "Type the price of the phone" << endl;
        cin >> price;
        phones.push_back(Phone(phoneName, modelName, formFactor, yearOfIssue, screenSizeInches, price));

        AddToBrands(phoneName);
        AddToSizePopularity(screenSizeInches);
    }

    void AddPhone(Phone phone)
    {
        phones.push_back(phone);
        AddToBrands(phone.GetPhoneName());
        AddToSizePopularity(phone.GetScreenSizeInches());
    }

    void DeletePhone()
    {
        phones.sort();
        int number;
        cout << "Which Phone do you want do delete? (choose number)\n";
        ShowPhones("", "");
        cin >> number;
        auto it = phones.begin();
        while (it->GetID() != number) {
            it++;
        }

        RemoveFromBrands(it->GetPhoneName());
        phones.erase(it);

    }

    void Report()
    {
        int step = 0;
        int skip;
        int choice;
        string secondChoice;
        system("CLS");
        cout << "Do you want to see the phones sorted:\n";
        cout << "By brand? (1)\n";
        cout << "By formFactor? (2)\n";
        cout << "By screen Size? (3)\n";
        cout << "Only the most popular brand? (4)\n";
        cout << "Top-3 screen sizes? (5)\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Which Brand?\n";

            for (auto itr = Brands.begin(); itr != Brands.end(); ++itr) 
            {
                cout << step << "\t" << itr->first << "\t" << "currently " << itr->second << " in stock." <<'\n';
                step++;
            }
            cin >> secondChoice;
            ShowPhones("Brand", secondChoice);

            cout << "\n(Press 1 to continue)";
            break;
        case 2:
            ReportFormFactor();
            cout << "Which one? (exp. FFS, SSF\n";
            cin >> secondChoice;
            ShowPhones("FF", secondChoice);
            cout << "\n(Press 1 to continue)";
            break;
        case 3:
            ReportScreenSize();
            cout << "What size? (exp. 6.0, 2.3)\n";
            cin >> secondChoice;
            ShowPhones("SS", secondChoice);
            cout << "\n(Press 1 to continue)";
            break;
        case 4:
            ReportMostPopularBrand();
            cout << "\n(Press 1 to continue)";
            break;
        case 5:
            ReportTopThree();
            cout << "\n(Press 1 to continue)";
            break;
        }

    }

    void ShowPhones(string type, string specific)
    {
        cout << "ID\t" << "Name\t" << "Model\t" << "FF\t" << "Year\t" << "Screen\t" << "Price\n";
        list <Phone> tempphones;

        int caseHolder = 3;
        if (type == "Brand")
            caseHolder = 1;
        if (type == "FF")
            caseHolder = 2;

        if (type == "") 
        {
            tempphones = phones;
        }
        else
        {
            switch (caseHolder)
            {
            case int(1) :
                for (auto p : phones)
                {
                    if (p.GetPhoneName() == specific)
                        tempphones.push_back(p);
                }
                break;
            case int(2) :
                for (auto p : phones)
                {
                    if (p.GetFormFactor() == specific)
                        tempphones.push_back(p);
                }
                break;
                case int(3) :
                for (auto p : phones)
                {
                    if (p.GetScreenSizeInches() == specific)
                        tempphones.push_back(p);
                }
                break;

            }
            
        }

        for (auto v : tempphones) {
            cout << v.GetID() << "\t";
            cout << v.GetPhoneName() << "\t";
            cout << v.GetPhoneModel() << "\t";
            cout << v.GetFormFactor() << "\t";
            cout << v.GetYearOfIssue() << "\t";
            cout << v.GetScreenSizeInches() << "\t";
            cout << v.GetPrice() << "\n";
        }
    }

    void ReportBrand() {
        phones.sort();
        ShowPhones("", "");
    }

    void ReportFormFactor() {
        phones.sort(FFComparator());
    }

    void ReportScreenSize() {
        phones.sort(ScreemSizeComparator());
    }
    void ReportMostPopularBrand() {
        int phoneQuantity = 0;
        string mostPopularBrand;
        for (auto itr = Brands.begin(); itr != Brands.end(); ++itr) {
            if (itr->second > phoneQuantity)
            {
                phoneQuantity = itr->second;
                mostPopularBrand = itr->first;
            }
        }
        cout << "\nCurrently the most popular brand is " << mostPopularBrand
            << " with " << phoneQuantity << " phones in our store!\n";

    }
    void ReportTopThree() 
    {
        auto it = SizePopularity.begin();
        cout << "Top 1. Screen Size: " << it->first << ", quantity: " << it->second << "\n";
        it++;
        cout << "Top 2. Screen Size: " << it->first << ", quantity: " << it->second << "\n";
        it++; 
        cout << "Top 3. Screen Size: " << it->first << ", quantity: " << it->second << "\n";        
    }

    void AddToBrands(string phonename) 
    {
        auto iterBrands = Brands.find(phonename);
        if (iterBrands == Brands.end()) {
            Brands.insert({ phonename, 1 });
        }
        else {
            iterBrands->second += 1;
        }
    }

    void AddToSizePopularity(string phonesize)
    {
        auto iter = SizePopularity.find(phonesize);
        if (iter == SizePopularity.end())
        {
            SizePopularity.insert({ phonesize, 1 });
        }
        else
            iter->second += 1;
    }

    void RemoveFromBrands(string phonename) {
        auto iterBrands = Brands.find(phonename);
        if (iterBrands != Brands.end())
            iterBrands->second -= 1;
    }
};

class Interface {

private:
    PhoneShop myPhoneShop;

public:

    void AddPhone(Phone phone)
    {
        myPhoneShop.AddPhone(phone);
    }

    void Start() {

        string skip = "";
        int choice;
        bool isInShop = true;

        while (isInShop) {
            system("CLS");
            cout << "Welcome to my humble store! What do you want to do?\n";
            cout << "Add a phone? Press 1\n";
            cout << "Delete a phone ? Press 2\n";
            cout << "Get a report? Press 3\n";
            cout << "I do not like your store. Press 4\n";

            cin >> choice;
            system("CLS");

            switch (choice) {
            case 1:
                myPhoneShop.AddPhone();
                cout << "Thanks for adding that phone. I couldn't do that without you.\n(Press 1 to continue)";
                cin >> skip;

                break;
            case 2:
                myPhoneShop.DeletePhone();
                cout << "Thanks for deleting that phone. I couldn't do that without you.\n(Press 1 to continue)";
                cin >> skip;
                break;
            case 3:
                myPhoneShop.Report();
                cin >> skip;

                break;
            case 4:
                isInShop = false;
                break;
            }
        }
    }

};

int main()
{
    Interface myInterface;
    myInterface.AddPhone(Phone("Samsung", "A01", "SFF", 1990, "2.0", 50.00));
    myInterface.AddPhone(Phone("Samsung", "A51", "SFF", 2020, "6.0", 2000.00));
    myInterface.AddPhone(Phone("Samsung", "S2", "SFF", 2018, "6.0", 3000.00));
    myInterface.AddPhone(Phone("Samsung", "A03", "SFF", 1990, "2.0", 50.00));
    myInterface.AddPhone(Phone("Huwawie", "2", "FFS", 1800, "5.0", 2000.00));
    myInterface.AddPhone(Phone("Huwawie", "65M", "FFS", 1800, "4.0", 2000.00));
    myInterface.AddPhone(Phone("Samsung", "S6", "SFF", 2018, "12.0", 8000.00));

    myInterface.Start();

    /*PhoneShop myPhoneShop;
    myPhoneShop.AddPhone(Phone("Samsung", "A01", "SFF", 1990, 2, 50.00));
    myPhoneShop.AddPhone(Phone("Samsung", "A51", "SFF", 2020, 6.5, 2000.00));
    myPhoneShop.AddPhone(Phone("Samsung", "S2", "SFF", 2018, 6.0, 3000.00));
    myPhoneShop.AddPhone(Phone("Samsung", "A03", "SFF", 1990, 2, 50.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "2", "FFS", 1800, 2, 2000.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "65M", "FFS", 1800, 4, 2000.00));
    myPhoneShop.AddPhone(Phone("Samsung", "S6", "SFF", 2018, 12.0, 8000.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "2", "FFS", 1800, 4, 2000.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "65M", "FFS", 1800, 6.0, 2000.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "2", "FFS", 1800, 2, 2000.00));
    myPhoneShop.AddPhone(Phone("Huwawie", "65M", "FFS", 1800, 8, 2000.00));

    //myPhoneShop.DeletePhone();

   // myPhoneShop.ShowPhones("Brand", "Samsung");

   // myPhoneShop.ShowPhones("", "");

    //for (auto itr = myPhoneShop.Brands.begin(); itr != myPhoneShop.Brands.end(); ++itr) 
     //   cout << itr->first << '\t' << itr->second << '\n';
   // myPhoneShop.ReportMostPopularBrand();

    myPhoneShop.ReportTopThree();// need to add remvoe form sizepopularity*/
    

}