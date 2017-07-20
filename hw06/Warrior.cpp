//
//  Warrior.cpp
//  hw06
//
//  Created by Kristen Ma on 4/7/15.
//  Copyright (c) 2015 Kristen Ma. All rights reserved.
//

#include "Warrior.h"
#include "Noble.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    
    void Warrior::display(ostream& os = cout) {
        os << "\t" << name << ": " << strength << endl;
    }
    
    string Warrior::getName() {
        return name;
    }
    
    double Warrior::getStrength() {
        return strength;
    }
    
    void Warrior::setStrength(double& ratio){
        if ( ratio == 0 ){
            strength = 0;
        }
        else {
            strength = strength - (strength*ratio);
        }
    }
    
    void Warrior::setBoss(Noble* aBoss){
        if (boss == nullptr) {
            boss = aBoss;
        }
    }
    
    void Warrior::runaway() {
        cout << name << " flees in terror, abandoning his lord, " << boss->getName() << endl;
        boss->deleteWarrior(this);
        boss = nullptr;
    }

}