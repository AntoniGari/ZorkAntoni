//
//  Area.cpp
//  
//
//  Created by Antoni Garí Romagosa on 6/11/15.
//
//

#include "Area.h"
#include <iostream>
using namespace std;

//BOLD
#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[0m"
//COLORS
#define CYAN "\033[0;36m"
#define GRAY "\033[1;30m"
#define GREEN "\033[1;32m"
#define LIGHT_CYAN "\033[1;36m"
#define LIGHT_GRAY "\033[0;37m"
//NO COLOR
#define NO_COLOR "\033[0m"

Area::Area() {
    this->north = NULL;
    this->east = NULL;
    this->south = NULL;
    this->west = NULL;
    this->up = NULL;
    this->down = NULL;
}

Area::Area(string name, string description) {
    this->name = name;
    this->description = description;
    this->north = NULL;
    this->east = NULL;
    this->south = NULL;
    this->west = NULL;
    this->up = NULL;
    this->down = NULL;
}

void Area::set(string name, string description) {
    this->name = name;
    this->description = description;
}

void Area::setItem(Item item) {
    this->items.push_back(item);
}

void Area::setDirection(char direction, Area *area) {
    switch (direction) {
        case 'n':
            north = area;
            break;
        case 'e':
            east = area;
            break;
        case 's':
            south = area;
            break;
        case 'w':
            west = area;
            break;
        case 'u':
            up = area;
            break;
        case 'd':
            down= area;
            break;
        default:
            break;
    }
}

Area * Area::goArea(char direction) {
    switch (direction) {
        case 'n':
            return north;
            break;
        case 'e':
            return east;
            break;
        case 's':
            return south;
            break;
        case 'w':
            return west;
            break;
        case 'u':
            return up;
            break;
        case 'd':
            return down;
            break;
        default:
            break;
    }
    return NULL;
}


void Area::addItem(Item item) {
    items.push_back(item);
}

void Area::deleteItem(int id) {
    list<Item>::iterator i;
    for (i = items.begin(); i != items.end(); ++i) {
        if(i->getId() == id) {
            //Erase item from this place
            items.erase(i);
        }
    }    
}

Item Area::getItem(string argument) {
    list<Item>::iterator i;
    Item aux = Item();
    for (i = items.begin(); i != items.end(); ++i) {
        if(i->getShortName() == argument) {
            aux = Item(i->getId(), i->getShortName(), i->getName(), i->getDescription());
            return aux;
        }
    }
    return aux;
}

void Area::printArea() {
    cout << BOLD_ON << name << BOLD_OFF << endl;
    cout << description << endl;
    list<Item>::iterator i;
    for (i = items.begin(); i != items.end(); ++i) {
        cout << "Hay " << i->getName() << " [" << i->getShortName() << "]" << endl;
    }

}