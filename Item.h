//
//  Item.h
//  
//
//  Created by Antoni Garí Romagosa on 16/11/15.
//
//

#ifndef Item_h
#define Item_h

#include <stdio.h>
#include <string>
using namespace std;

class Item {
private:
    int id;
    string shortName;
    string name;
    string description;
public:
    Item();
    Item(int,string,string,string);

    int getId();
    string getShortName();
    string getName();
    string getDescription();
    //~Item();
    /*
    void copyItem(Item);
    void deleteItem();
    int getId();
    string getName();
    string getDescription();
    void printId();
    void printName();
    void printDescription();
    void setId(int);
    void setName(string);
    void setDescription(string);*/
};





#endif /* Item_h */
