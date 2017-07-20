//
//  submission: hw03.cpp
//  programmer: kristen ma
//  n19680951
//  knm316
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior{
public:
    Warrior(const string aName, int theStrength) : name(aName), strength(theStrength){}
    
    void display(ostream& os = cout) const{
        os << "\t" << name << ": " << strength << endl;
    }
    
    string getName() const {
        return name;
    }
    
    int getStrength() const {
        return strength;
    }
    
     void setStrength(int ratio){
         if ( ratio == 0 ){
             strength = 0;
         }
         else {
             strength = strength - (strength*ratio);
         }
    }
         
private:
    string name;
    int strength;
};

class Army{
public:
    Army() : strength(0), warriors(NULL){}
    
    void display(ostream& os = cout) const{
        int vectorSize = 0;
        for (int indx = 0; indx < warriors.size(); indx++){
            vectorSize += 1;
        }
        os << warriors.size() << endl;
        for (int i = 0; i < warriors.size(); i++){
            warriors[i]->display(os);
        }
    }
    
    void hire(Warrior aWarrior){
        Warrior* warrior = new Warrior(aWarrior);
        warriors.push_back(warrior);
    }
    
    void fire(Warrior aWarrior){
        for (int i = 0; i < warriors.size(); i++){
            if (aWarrior.getName() == warriors[i]->getName()){
                for (int j = i; j < warriors.size(); j++){
                    warriors[j] = warriors[j+1];
                }
            }
        }
        warriors.pop_back();
    }
    
    int getStrength(){
        int strength = 0;
        for (int i = 0; i < warriors.size(); i++){
            strength += warriors[i]->getStrength();
        }
        return strength;
    }
    
    int setStrength(int newStrength){
        for (int i = 0; i < warriors.size(); i++){
            warriors[i]->setStrength(newStrength);
            strength += warriors[i]->getStrength();
        }
        return strength;
    }
    
    void reset(){
        for (int i = 0; i < warriors.size(); i++){
            delete warriors[i];
            warriors[i] = NULL;
        }
        warriors.clear();
    }

private:
    int strength;
    vector<Warrior*> warriors;
};

class Noble{
public:
    Noble(const string aName) : name(aName){}

    void battle(Noble aNoble, ostream& os = cout){
        int strength = army.getStrength();
        
        os << name << " battles " << aNoble.name << "." << endl;
        
        if ( strength > aNoble.army.getStrength()){
            if (aNoble.army.getStrength() == 0){
                cout << "He's dead, " << name << "." << endl;
            }
            else {
                cout << name << " defeats " << aNoble.name << "." << endl;
                army.setStrength(aNoble.army.getStrength()/strength);
                aNoble.army.setStrength(0);
            }
        }
        else if (strength < aNoble.army.getStrength()) {
            if (strength == 0){
                cout << "He's dead, " << aNoble.name << "." << endl;
            }
            else {
                cout << aNoble.name << " defeats " << name << "." << endl;
                aNoble.army.setStrength(strength/aNoble.army.getStrength());
                army.setStrength(0);
            }
        }
        else if (strength == aNoble.army.getStrength()){
            if (strength == 0 && aNoble.army.getStrength() == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else{
                cout << "Mutual Annihilation: " << name << " and " << aNoble.name << " die in each other's hands." << endl;
                army.setStrength(0);
                aNoble.army.setStrength(0);
            }
        }
    }
    
    void hire(Warrior aWarrior){
        army.hire(aWarrior);
    }
    
    void display(ostream& os = cout) const{
        os << name << " has an army of ";
        army.display(os);
        os << endl;
    }
    
    void fire(Warrior aWarrior, ostream& os = cout){
        army.fire(aWarrior);
        os << aWarrior.getName() << ", you're fired! -- " << name << endl;
    }
private:
    string name;
    Army army;

};



int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();

    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
    system("pause");
    
    return 0;
}
