
//
//  Warrior.h
//  hw06
//

#ifndef WARRIOR_H
#define WARRIOR_H
#include <vector>
#include <string>

namespace WarriorCraft{
    
    class Noble;
    class Warrior{
        
    public:
        Warrior(const std::string aName, int theStrength) : name(aName), strength(theStrength), boss(nullptr){}
        
        void display(std::ostream&);
        std::string getName();
        double getStrength();
        void setStrength(double& ratio);
        void setBoss(Noble* aNoble);
        void runaway();

    private:
        std::string name;
        int strength;
        Noble* boss;
    };
}

#endif
