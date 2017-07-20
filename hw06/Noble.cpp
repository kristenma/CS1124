//
//  Noble.cpp
//  hw06
//
//  Created by Kristen Ma on 4/7/15.
//  Copyright (c) 2015 Kristen Ma. All rights reserved.
//

#include "Noble.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    
    
    void Noble::battle(Noble& aNoble){
        double strength = this->getStrength();
        
        cout << name << " battles " << aNoble.name << "." << endl;
        
        if ( strength > aNoble.getStrength()){
            if (aNoble.getStrength() == 0){
                cout << "He's dead, " << name << "." << endl;
            }
            else {
                cout << name << " defeats " << aNoble.name << "." << endl;
                this->setStrength(aNoble.getStrength()/strength);
                aNoble.setStrength(0);
            }
        }
        else if (strength < aNoble.getStrength()) {
            if (strength == 0){
                cout << "He's dead, " << aNoble.name << "." << endl;
            }
            else {
                cout << aNoble.name << " defeats " << name << "." << endl;
                aNoble.setStrength(strength/aNoble.getStrength());
                this->setStrength(0);
            }
        }
        else if (strength == aNoble.getStrength()){
            if (strength == 0 && aNoble.getStrength() == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else{
                cout << "Mutual Annihilation: " << name << " and " << aNoble.name << " die in each other's hands." << endl;
                this->setStrength(0);
                aNoble.setStrength(0);
            }
        }
    }
    
    string Noble::getName() {
        return name;
    }
    
    void Noble::hire(Warrior& aWarrior){
        Warrior* warrior = new Warrior(aWarrior);
        army.push_back(warrior);
        aWarrior.setBoss(this);
    }
    
    double Noble::getStrength() {
        double strength = 0;
        for (size_t i = 0; i < army.size(); i++){
            strength += army[i]->getStrength();
        }
        return strength;
    }
    
    void Noble::setStrength(double newStrength){
        double strength = 0;
        for (size_t i = 0; i < army.size(); i++){
            army[i]->setStrength(newStrength);
            strength += army[i]->getStrength();
        }
    }
    
    void Noble::deleteWarrior(Warrior* aWarrior){
        for (size_t i = 0; i < army.size(); i++){
            if (aWarrior->getName() == army[i]->getName()){
                for (size_t j = i; j < army.size(); j++){
                    army[j] = army[j+1];
                }
            }
        }
        army.pop_back();
    }
    
    void Noble::reset(){
        for (size_t i = 0; i < army.size(); i++){
            delete army[i];
            army[i] = NULL;
        }
        army.clear();
    }
    
    ostream& operator << (ostream& os, const Noble& aNoble) {
        os << aNoble.name << " has an army of ";
        os << aNoble.army.size() << endl;
        for (int i = 0; i < aNoble.army.size(); i++){
            aNoble.army[i]->display(os);
        }
        return os;
    }
}