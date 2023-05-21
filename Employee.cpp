#include "Employee.h"
#include "Inventory.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void Employee::display() {
	cout << left << setw(7) << ID;
	cout << left << setw(20) << name;
	cout << left << setw(10) << salary;
	cout << left << setw(20) << annual_salary;
	cout << endl;
}
void Cashier::display() {
	cout << left << setw(7) << ID;
	cout << left << setw(20) << name;
	cout << left << setw(10) << salary;
	cout << left << setw(20) << annual_salary;
	cout << endl;
}
void Cashier::display(Cashier* cashier, int n)
{
	/*cout << "ID : " << ID << endl;
	cout << "Name : " << name << endl;
	cout << "Salary : " << salary << endl;
	cout << "Annual salary : " << annual_salary << endl;*/
	cout << left << setw(7) << "ID";
	cout << left << setw(20) << "Name";
	cout << left << setw(10) << "Salary";
	cout << left << setw(20) << "Annual Salary";
	cout << endl << endl;
	for (int i = 0; i < n; i++) {
		/*int l = strlen(cashier[i].name);
		for (int j = 0; j < l; j++) {
			if (cashier[i].name[j] == '_')
				cashier[i].name[j] = ' ';
		}*/
		cout << left << setw(7) << cashier[i].ID;
		cout << left << setw(20) << cashier[i].name;
		cout << left << setw(10) << cashier[i].salary;
		cout << left << setw(20) << cashier[i].annual_salary;
		/*for (int j = 0; j < l; j++) {
			if (cashier[i].name[j] == ' ')
				cashier[i].name[j] = '_';
		}*/
		cout << endl;
	}
	cout << endl;
}

void Employee::setdata(ifstream& input)
{
	input >> ID;
	input >> name;
	input >> salary;
	input >> annual_salary;
	input >> password;
}

void Employee::setID(int id)
{
	ID = id;
}

void Employee::setname(string nam)
{
	name = nam;
}

void Employee::setsalary(double s)
{
	salary = s;
}

void Employee::setannualsalary(double ans)
{
	annual_salary = ans;
}

void Employee::setpassword(string pass) {
	password = pass;
}

string Employee::getpassword()
{
	return password;
}

string Employee::getname()
{
	return name;
}

int Employee::getID() {
	return ID;
}

double Employee::getSalary() {
	return salary;
}

double Employee::getAnnualSalary() {
	return annual_salary;
}

void Manager::menu(Manager* manager, Cashier* cashier, int& noofcashiers, Item* items, int& tItem, int& tCategory)
{
	int ch;
	cout << "Welcome to NFT Super Market Management System\n";
	cout << "Select one of the following options :- \n";
	cout << "1: Manage Cashier.\n";
	cout << "2: Billing.\n";
	cout << "3: View Items by Category.\n";
	cout << "4: Edit Inventory.\n";
	cin >> ch;
	while (!(ch >= 1 && ch <= 4))
	{
		cout << "Enter again::";
		cin >> ch;
	}
	// 1. Cashier, 2. Manager
	if (ch == 1)
	{
		manager->updatecashiermenu(manager, cashier, noofcashiers);

	}
	if (ch == 2) {
		manager->billing(items, tItem);
	}
	if (ch == 3) {
		manager->viewByCategory(items, tItem, tCategory);
	}
	if (ch == 4) {
		manager->editInventory(manager, items, tItem);
	}
}

void Manager::updatecashiermenu(Manager* manager, Cashier* cashier, int& noofcashiers)
{
	// Functions
/*
~ Add a cashier
~ Remove a cashier
~ Change a cashier's salary
~ View all cashier's detail
*/
	int cashierchange;
	cout << "1: Add new cashier\n2: Remove a cashier\n3: Change cashier's salary\n4: View all cashier's detail\n";
	cin >> cashierchange;
	while (!(cashierchange >= 1 && cashierchange <= 4))
	{
		cout << "Enter again!";
		cin >> cashierchange;//cashier update menu's option 
	}
	if (cashierchange == 1)
	{
		manager->addCashier(cashier, noofcashiers);

	}
	else if (cashierchange == 2)
	{
		manager->removeCashier(cashier, noofcashiers);
	}
	else if (cashierchange == 3)
	{
		manager->changeSalary(cashier, noofcashiers);
	}
	else
	{
		// view all cashier's data
		cashier->display(cashier, noofcashiers);
	}
}

void Manager::addCashier(Cashier* arr, int& n) {
	int prevSize = n;
	Cashier* temp = new Cashier[n];
	for (int i = 0; i < n; i++)
		temp[i] = arr[i];
	n++;
	arr = new Cashier[n];
	for (int i = 0; i < prevSize; i++)
		arr[i] = temp[i];

	//details of new cashier
	string cashName, password;
	int cashID;
	double cashsalary, cashAnnual;
	cout << "Enter ID of New Cashier: ";
	cin >> cashID;
	cout << "Enter Name of New Cashier: ";
	cin >> cashName;
	cout << "Enter Monthly Salary of New Cashier: ";
	cin >> cashsalary;
	cout << "Enter Annual Salary of New Cashier: ";
	cin >> cashAnnual;
	cout << "Enter Password of New Cashier: ";
	cin >> password;
	//writing to file
	ofstream write;
	write.open("cashier.txt");
	write << n << "\n";
	for (int i = 0; i < prevSize; i++) {
		write << arr[i].getID() << " " << arr[i].getname() << " " << arr[i].getSalary() << " " << arr[i].getAnnualSalary() << " " << arr[i].getpassword() << endl;
	}
	write.close();
	write.open("cashier.txt", ios_base::app);
	write << cashID << " " << cashName << " " << cashsalary << " " << cashAnnual << " " << password << endl;
	write.close();
	ifstream input;
	input.open("cashier.txt");
	arr[prevSize].setdata(input);
	input.close();
}

void Manager::removeCashier(Cashier* arr, int& n) {
	int removeID;
	int index = 0;
	bool found = false;
	do {
		cout << "Enter ID of Cashier to Remove: ";
		cin >> removeID;
		
		for (int i = 0; i < n; i++) {
			if (removeID == arr[i].getID()) {
				found = true;
				index = i;
			}
		}
		if (!found)
			cout << "Cashier with ID " << removeID << " Does Not Exist\n";
	} while (!found);
		cout << "Removed Cashier " << arr[index].getname() << endl;
		Cashier* temp = new Cashier[n - 1];
		for (int i = 0, j = 0; i < n; i++) {
			if (index == i)
				continue;
			else {
				temp[j] = arr[i];
				j++;
			}
		}
		n--;
		arr = new Cashier[n];
		for (int i = 0; i < n; i++)
			arr[i] = temp[i];
		ofstream write;
		write.open("cashier.txt");
		write << n << "\n";
		for (int i = 0; i < n; i++) {
			write << arr[i].getID() << " " << arr[i].getname() << " " << arr[i].getSalary() << " " << arr[i].getAnnualSalary() << " " << arr[i].getpassword() << endl;
		}
		write << "";
		write.close();
	
}

void Manager::changeSalary(Cashier* arr, int n) {
	int index = 0;
	int cashID;
	cout << "Search Cashier by ID: ";
	cin >> cashID;
	bool found = false;
	for (int i = 0; i < n; i++) {
		if (cashID == arr[i].getID()) {
			index = i;
			found = true;
		}
	}
	if (!found)
		cout << "Cashier with ID " << cashID << " does not exist\n";
	else {
		cout << "Change Salary of Cashier " << arr[index].getname() << endl;
		double newSalary;
		cout << "Enter New Monthly Salary: ";
		cin >> newSalary;
		arr[index].setsalary(newSalary);
		arr[index].setannualsalary(newSalary * 12);
		ofstream write;
		write.open("cashier.txt");
		write << n << "\n";
		for (int i = 0; i < n; i++) {
			write << arr[i].getID() << " " << arr[i].getname() << " " << arr[i].getSalary() << " " << arr[i].getAnnualSalary() << " " << arr[i].getpassword() << endl;
		}
		write.close();
	}
}

void Manager::managerLogin(Manager* manager) {
	string password;
	cout << "Enter password : ";
	cin.ignore();
	getline(cin, password);
	while (!(password == manager->getpassword()))
	{
		cout << "Incorrect, Enter again!\n";
		getline(cin, password);
	}
	cout << "Welcome " << manager->getname() <<"!" << endl;
}

//void Manager::billing() {
//	int numItem, tItem, tCategory;
//	fstream fin;
//	fin.open("inventory.txt");
//	fin >> tItem;
//	fin >> tCategory;
//	fin.close();
//	Item* items = new Item[tItem];
//	items->inputFromFile(items, tItem);
//	items->display(items, tItem);
//	numItem = items->getCartItems(tItem);
//	Item* cart = new Item[numItem];
//	cart->inputCart(cart, items, tItem, numItem);
//	float bill = cart->calculateBill(cart, numItem);
//	cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
//	cart->display(cart, numItem, bill);
//	cout << endl;
//}

void Employee::viewByCategory(Item* items, int tItem, int tCategory) {
	char** catName = new char* [tCategory];
	for (int i = 0; i < tCategory; i++) {
		catName[i] = new char[50];
	}
	catName[0] = items[0].getCategory();
	int n = 1;
	bool match = false;
	for (int i = 1; i < tItem; i++) {
		match = false;
		for (int j = 0; j < tCategory; j++) {
			if (strcmp(items[i].getCategory(), catName[j]) == 0)
				match = true;
		}
		if (!match) {
			catName[n] = items[i].getCategory();
			n++;
		}
	}
	int choice;
	cout << "Item Categories: \n";
	for (int i = 0; i < tCategory; i++) {
		cout << i + 1 << ": ";
		cout << catName[i] << endl;
	}
	do {
		cout << "Enter Category index number to Search: ";
		cin >> choice;
		if (choice - 1 < 0 || choice - 1 > tCategory)
			cout << "Please enter a valid number.\n";
	} while (choice - 1 < 0 || choice - 1 > tCategory);
	cout << endl;
	for (int i = 0; i < tItem; i++) {
		if (strcmp(items[i].getCategory(), catName[choice - 1]) == 0)
			items[i].display();
	}
	
}

void Manager::editInventory(Manager* manager, Item* arr, int& tItem) {
	int choice;
	cout << "1. Add a New Item\n2. Remove an Item\n";
	cin >> choice;
	while (!(choice == 1 || choice == 2)) {
		cout << "Invalid Input, Enter Again\n";
		cin >> choice;
	}
	if (choice == 1)
		manager->addItem(arr, tItem);
	if (choice == 2)
		manager->removeItem(arr, tItem);
}

void Manager::addItem(Item* arr, int& tItem) {
	int prevSize = tItem;
	Item* temp = new Item[tItem];
	for (int i = 0; i < tItem; i++)
		temp[i] = arr[i];
	tItem++;
	arr = new Item[tItem];
	for (int i = 0; i < prevSize; i++)
		arr[i] = temp[i];

	//details of new item
	char name[50];
	int ID, quan;
	double price;
	string category;
	cout << "Enter ID of New Item: ";
	cin >> ID;
	cout << "Enter Name of New Item: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter Category of New Item: ";
	getline(cin, category);
	cout << "Enter Quantity of New Item: ";
	cin >> quan;
	cout << "Enter Price of New Item: ";
	cin >> price;
	//writing to file
	ofstream write;
	write.open("inventory.txt");
	write << tItem << "\n";
	for (int i = 0; i < prevSize; i++) {
		write << arr[i].getID() << " " << arr[i].getName() << " " << arr[i].getCategory() << " " << arr[i].getQuantity() << " " << arr[i].getPrice() << endl;
	}
	write.close();
	write.open("inventory.txt", ios_base::app);
	write << ID << " " << name << " " << category << " " << quan << " " << price << endl;
	write.close();
	arr->inputFromFile(arr, tItem);
}

void Manager::removeItem(Item* arr, int& tItem) {
	int removeID;
	int index = 0;
	bool found = false;
	do {
		cout << "Enter ID of Item to Remove: ";
		cin >> removeID;
		for (int i = 0; i < tItem; i++) {
			if (removeID == arr[i].getID()) {
				found = true;
				index = i;
				break;
			}
		}
		if (!found)
			cout << "Item with ID " << removeID << " Does Not Exist\n";
	} while (!found);
	cout << "Removed Item ";
	char* temp1;
	temp1 = arr[index].getName();
		int n = strlen(arr[index].getName());
		for (int i = 0; i < n; i++) {
			if (temp1[i] == '_')
				cout << " ";
			else
				cout << temp1[i];
		}
		Item* temp = new Item[tItem - 1];
		for (int i = 0, j = 0; i < tItem; i++) {
			if (index == i)
				continue;
			else {
				temp[j] = arr[i];
				j++;
			}
		}
		tItem--;
		arr = new Item[tItem];
		for (int i = 0; i < tItem; i++)
			arr[i] = temp[i];
		arr->updateInventory(arr, tItem);
	
}


void Cashier::cashiers(int index)
{
	cout << index << ": " << name << endl;
}

void Cashier::cashierLogin(Cashier* cashier, int noofcashiers, int& cashIndex) {
	cout << "Choose?\n";
	int cashier_no;
	for (int i = 0; i < noofcashiers; i++)
		cashier[i].cashiers(i + 1);
	cin >> cashier_no;
	while (!(cashier_no > 0 && cashier_no <= noofcashiers))
	{
		cout << "Enter again!\n";
		cin >> cashier_no;
	}
	cashier_no--; // index selected for specific cashier

	string password;
	cout << "Enter password : ";
	cin.ignore();
	getline(cin, password);
	while (!(password == cashier[cashier_no].getpassword()))
	{
		cout << "Incorrect, Enter again!\n";
		getline(cin, password);
	}
	cout << "Logged in as : " << cashier[cashier_no].getname() << endl;
	cashIndex = cashier_no;
}

void Cashier::menu(Cashier* arr, int index, Item* items, int tItem, int tCategory) {
	int ch;
	cout << "Welcome to NFT Super Market Management System\n";
	cout << "Select one of the following options :- \n";
	cout << "1: View Your Details.\n";
	cout << "2: Billing.\n";
	cout << "3: View Items by Category. \n";
	cin >> ch;
	while (!(ch >= 1 && ch <= 3))
	{
		cout << "Enter again::";
		cin >> ch;
	}
	if (ch == 1) {
		arr[index].display();
	}
	if (ch == 2) {
		arr->billing(items, tItem);
	}
	if (ch == 3) {
		arr->viewByCategory(items, tItem, tCategory);
	}
}

void Employee::billing(Item* items, int tItem) {
	int numItem;
	items->display(items, tItem);
	numItem = items->getCartItems(tItem);
	Item* cart = new Item[numItem];
	cart->inputCart(cart, items, tItem, numItem);
	float bill = cart->calculateBill(cart, numItem);
	cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
	cart->display(cart, numItem, bill);
	cout << endl;
	cout << "Are you a registered customer?(y/n): ";
	char ch;
	bool check = false;
	do {
		cin >> ch;
		if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')
			check = true;
		else
			cout << "Invalid Input, Enter Again\n";

	} while (!check);
	if (ch == 'y' || ch == 'Y') {
		Customer* customers;
		int tCustomers;
		ifstream input;
		input.open("customer.txt");
		input >> tCustomers;
		customers = new Customer[tCustomers];
		for (int i = 0; i < tCustomers; i++)
			customers[i].inputData(input);
		input.close();
		int cIndex;
		cIndex = customers->customerLogin(customers, tCustomers);
		char choice;
		cout << "Would you like to use your loyalty points?(y/n): ";
		bool x = false;
		while (!x) {
			cin >> choice;
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
				x = true;
			else
				cout << "Invalid Input, Enter Again\n";
		}
		if (choice == 'y' || choice == 'Y') {
			int points = customers[cIndex].getPoints();
			float bill = cart->loyaltyBill(cart, numItem, points);
			cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
			cart->display(cart, numItem, bill);
			cout << endl;
			customers[cIndex].resetPoints(bill);
			customers->writeToFile(customers, tCustomers);
		}
		else {
			cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
			cart->display(cart, numItem, bill);
			cout << endl;
			customers[cIndex].addPoints(bill);
			customers->writeToFile(customers, tCustomers);
		}
	}
	else {
		char choice = 0;
		cout << "Would you like to get registered?(y/n): ";
		bool x = false;
		while (!x) {
			cin >> choice;
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
				x = true;
			else
				cout << "Invalid Input, Enter Again\n";
		}
		if (choice == 'y' || choice == 'Y') {
			Customer* customers;
			int tCustomers;
			ifstream input;
			input.open("customer.txt");
			input >> tCustomers;
			customers = new Customer[tCustomers];
			for (int i = 0; i < tCustomers; i++)
				customers[i].inputData(input);
			input.close();
			customers->addCustomer(customers, tCustomers, bill);
			cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
			cart->display(cart, numItem, bill);
			cout << endl;
		}
		else {
			cout << "\n    YOUR CART IS AS FOLLOWS:   \n";
			cart->display(cart, numItem, bill);
			cout << endl;
		}
	}
}

//void Cashier::viewByCategory(Item* items, int tItem) {
//	string type;
//	cout << "Item Categories: \n";
//	cout << "Selfcare\nDrinks\nSnacks\n";
//	cout << "Enter Category to Search: ";
//	cin.ignore();
//	getline(cin, type);
//	bool flag = false;
//	while (!flag) {
//		bool exists = false;
//		for (int i = 0; i < tItem; i++) {
//			if (type == items[i].getCategory())
//				exists = true;
//		}
//		if (!exists) {
//			cout << "Invalid Input, Enter Again: ";
//			//cin.ignore();
//			getline(cin, type);
//		}
//		else {
//			for (int i = 0; i < tItem; i++) {
//				if (items[i].getCategory() == type)
//					items[i].displayItem();
//			}
//			flag = true;
//		}
//	}
//}
