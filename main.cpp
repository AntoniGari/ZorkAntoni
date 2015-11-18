//
//  main.cpp
//  
//
//  Created by Antoni Garí Romagosa on 6/11/15.
//
//

#include <iostream>
#include <string>
using namespace std;

#include "Area.h"
#include "World.h"
// #include "main.hpp"

int main () {
    string sentence;
    World world;

    //The introduction of the game
    world.introduction();
    
    //The first zone
    world.actualArea();
    while (!world.isFinished()) {
        cout << endl << ">";
        getline(std::cin, sentence);
        world.action(sentence);
    }
    
    world.end();
    
    return 0;
}