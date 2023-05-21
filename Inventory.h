#ifndef Inventory_H
#define Inventory_H
#include<iostream>
#include<fstream>
using namespace std;

class Inventory {
protected:
	char itemName[50];
	int itemID;
	double unitPrice;
	int quantity;
public:
	Inventory() {}
};

class Category :public Inventory {
protected:
	char itemCategory[50];
public:
	Category() {}
	char* getCategory();
};

class Item :public Category {
private:

public:
	Item() {}
	void inputFromFile(Item*, int);
	void checkReorder();
	void display(Item*, int);//display inventory
	void display();//display item
	int getID();
	int getQuantity();
	int getPrice();
	char* getName();
	void setQuantity(int);
	void inputCart(Item*, Item*, int, int&);
	int getCartItems(int);
	float calculateBill(Item*, int);
	void updateInventory(Item*, int);
	float loyaltyBill(Item*, int, int);
	void display(Item*, int, float);//display cart
};


#endif
