
//
//  Noble.h
//  hw06
//

#ifndef NOBLE_H
#define NOBLE_H
#include <vector>
#include <string>

namespace WarriorCraft{
    
    class Warrior;
    class Noble{
        friend std::ostream& operator << (std::ostream&, const Noble&);
    public:
        Noble(const std::string aName) : name(aName){}
        
        void battle(Noble& aNoble);
        std::string getName();
        void display(std::ostream& os);
        void hire(Warrior& aWarrior);
        double getStrength();
        void setStrength(double newStrength);
        void deleteWarrior(Warrior* aWarrior);
        void reset();

    private:
        std::string name;
        std::vector<Warrior*> army;
        
    };
}

#endif
