//
//  World.h
//  
//
//  Created by Antoni Garí Romagosa on 14/11/15.
//
//

#ifndef World_h
#define World_h

#include <list>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Area.h"
#include "Item.h"
using namespace std;

class World {
private:
    Area puertaHierro;
    Area estatua;
    Area puertaCasa;
    Area recibidor;
    Area salon;
    Area salita;
    Area primerPiso;
    
    bool finished;
    Area *actual;
    list<Item> items;
public:
    World();
    void action(string);
    void actualArea();
    void introduction();
    bool isFinished();
    void end();
};

#endif /* World_h */
