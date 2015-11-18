//
//  Area.h
//  
//
//  Created by Antoni Garí Romagosa on 6/11/15.
//
//

#ifndef Area_h
#define Area_h

#include <list>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Item.h"
using namespace std;

class Area {
    string name;
    string description;
    Area *north;
    Area *east;
    Area *south;
    Area *west;
    Area *up;
    Area *down;
    list<Item> items;
public:
    Area();
    Area(string,string);
    void set(string,string);
    void setItem(Item);
    void setDirection(char, Area *);
    Area* goArea(char direction);
    void addItem(Item);
    void deleteItem(int);
    Item getItem(string);
    void printArea();
};

#endif /* Area_h */
