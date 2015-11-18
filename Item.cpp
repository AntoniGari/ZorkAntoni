//
//  Item.cpp
//  
//
//  Created by Antoni Garí Romagosa on 16/11/15.
//
//

#include "Item.h"
#include <iostream>
using namespace std;

Item::Item() {
    this->id = 0;
    this->shortName = "";
    this->name = "";
    this->description = "";
}


Item::Item(int id, string shortName, string name, string description) {
    this->id = id;
    this->shortName = shortName;
    this->name = name;
    this->description = description;
}

int Item::getId() {
    return id;
}

string Item::getShortName() {
    return shortName;
}

string Item::getName() {
    return name;
}

string Item::getDescription() {
    return description;
}

//~Item();
/*
void Item::copyItem(Item item) {
    this->id = item.getId();
    this->name = item.getName();
    this->description = item.getDescription();
}*/

//void deleteItem();
/*
int getId() {
    return id;
}

string getDescription() {
    return description;
}

void printId() {
    cout << this->id << endl;
}

void printName() {
    cout << this->name << endl;
}

void printDescription() {
    cout << this->description << endl;
}

void setId(int id) {
    this->id = id;
}

void setName(string name) {
    this->name = name;
}

void setDescription(string description) {
    this->description = description;

}*/