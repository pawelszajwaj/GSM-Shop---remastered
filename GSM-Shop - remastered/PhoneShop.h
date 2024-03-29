#pragma once

#include <iostream>
#include <list>
#include <string>
#include <map>
#include "Phone.h";
#include <fstream>

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
        string yearOfIssue;
        string screenSizeInches;
        string price;
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

    void DeletePhone(int number)
    {
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
                cout << step << "\t" << itr->first << "\t" << "currently " << itr->second << " in stock." << '\n';
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
        cout << "ID\t\t" << "Name\t\t" << "Model\t\t" << "FF\t\t" << "Year\t\t" << "Screen\t\t" << "Price\n";
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
            cout << v.GetID() << "\t\t";
            cout << v.GetPhoneName() << "\t\t";
            cout << v.GetPhoneModel() << "\t\t";
            cout << v.GetFormFactor() << "\t\t";
            cout << v.GetYearOfIssue() << "\t\t";
            cout << v.GetScreenSizeInches() << "\t\t";
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

    void RemoveFromSizePopularity(string phonesize)
    {
        auto iterBrands = Brands.find(phonesize);
        if (iterBrands != Brands.end())
            iterBrands->second -= 1;
    }

    void RemoveFromBrands(string phonename) {
        auto iterBrands = Brands.find(phonename);
        if (iterBrands != Brands.end())
            iterBrands->second -= 1;
    }

    void ReadFromFile(string file)
    {
        string mystring;
        string phoneArray[6];
        int i = 0;
        int phoneToDelete = -1 + phones.size();
        ifstream data(file);
        if (data.is_open())
        {
            while (data)
            {
                size_t pos = 0;
                string token;
                string delimiter = "\t";
                i = 0;
                getline(data, mystring);
                while ((pos = mystring.find(delimiter)) != string::npos)
                {
                    token = mystring.substr(0, pos);
                    mystring.erase(0, pos + delimiter.length());
                    //cout << token << endl;
                    phoneArray[i] = token;
                    i++;
                }
                phoneArray[5] = mystring;
                AddPhone(Phone(phoneArray[0], phoneArray[1], phoneArray[2], phoneArray[3], phoneArray[4], phoneArray[5]));
                phoneToDelete++;
            }
            if(phoneToDelete != -1)
                DeletePhone(phoneToDelete);
            data.close();
        }
    }

    void WriteToFile(string file)
    {
        ofstream writeFile(file);

        writeFile << "Name\t\t" << "Model\t\t" << "FF\t\t" << "Year\t\t" << "Screen\t\t" << "Price\n";
        writeFile << "\n";

        for (auto p : phones)
        {
            writeFile << p.GetPhoneName() << "\t\t";
            writeFile << p.GetPhoneModel() << "\t\t";
            writeFile << p.GetFormFactor() << "\t\t";
            writeFile << p.GetYearOfIssue() << "\t\t";
            writeFile << p.GetScreenSizeInches() << "\t\t";
            writeFile << p.GetPrice() << "\n";
        }

        writeFile.close();
    }
};