#include<iostream>
#include<string>
#include<fstream>
#include"Employee.h"
#include"Inventory.h"
#include "Customer.h"

using namespace std;

int main()
{
    ifstream input;
    Cashier* cashier = nullptr;
    Manager* manager = nullptr;
    Item* items = nullptr;
    int choice;
    bool backmenu = false;
    do {
        cout << "Who is logging in? Select :\n";
        cout << "1: Cashier\n2: Manager\n";
        cin >> choice;
        while (!(choice == 1 || choice == 2))
        {
            cout << "Enter again!\n";
            cout << "1: Cashier\n2: Manager";
            cin >> choice;
        }

        //copying cashier data to main method
        int noofcashiers = 0;
        input.open("cashier.txt");
        input >> noofcashiers;
        cashier = new Cashier[noofcashiers];
        for (int i = 0; i < noofcashiers; i++)
            cashier[i].setdata(input);
        input.close();

        //copying manager data to main method
        input.open("manager.txt");
        manager = new Manager;
        manager->setdata(input);
        input.close();

        //copying item data to main
        int numItem, tItem, tCategory;
        input.open("inventory.txt");
        input >> tItem;
        input >> tCategory;
        input.close();
        items = new Item[tItem];
        items->inputFromFile(items, tItem);
        bool c1;
            if (choice == 1) {
                int cashIndex;
                cashier->cashierLogin(cashier, noofcashiers, cashIndex);
                system("cls");
                do {
                    cashier->menu(cashier, cashIndex, items, tItem, tCategory);
                    cout << "Do you want to go back to Cashier menu? (1/0)";
                    cin >> c1;
                    if (c1)
                        system("cls");
                } while (c1);
            }
            else if (choice == 2) {
                manager->managerLogin(manager);
                system("cls");
                do {
                    manager->menu(manager, cashier, noofcashiers, items, tItem, tCategory);
                    cout << "Do you want to go back to Manager menu? (1/0)";
                    cin >> c1;
                    if (c1)
                        system("cls");
                } while (c1);
            }
        cout << "Do you want to go to login page? (1/0)";
        cin >> backmenu;
        if (backmenu)
            system("cls");
    }while(backmenu);
    delete manager;
    delete[] cashier;
    delete[] items;
    cout << endl;
    system("pause");
    return 0;
}