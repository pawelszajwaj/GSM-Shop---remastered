#pragma once

#include "Phone.h"
#include "PhoneShop.h"

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