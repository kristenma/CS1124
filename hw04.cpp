//
//  submission: hw04.cpp
//  programmer: kristen ma
//  n19680951
//  knm316
//
//

#include <iostream>
#include <fstream>
#include <string>
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
    
    double getStrength() const {
        return strength;
    }
    
    void setStrength(double ratio){
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
                for (int j = i+1; j < warriors.size(); j++){
                    warriors[j-1] = warriors[j];
                }
            }
        }
        warriors.pop_back();
    }
    
    double getStrength(){
        strength = 0;
        for (int i = 0; i < warriors.size(); i++){
            strength += warriors[i]->getStrength();
        }
        return strength;
    }
    
    double setStrength(double newStrength){
        for (size_t i = 0; i < warriors.size(); i++){
            warriors[i]->setStrength(newStrength);
            strength += warriors[i]->getStrength();
        }
        return strength;
    }
    
    void reset(){
        for (size_t i = 0; i < warriors.size(); i++){
            delete warriors[i];
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
        double strength = army.getStrength();
        
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
        os << "You don't work for me anymore, " << aWarrior.getName() << "!  -- " << name << endl;
    }
    
    string getName(){
        return name;
    }
    
    void reset(){
        army.reset();
    }
private:
    string name;
    Army army;
    
};

//reads through the warrior file and acts accordingly
void readFile(ifstream& war){
    string action;
    string warrior;
    string nobleOne;
    string nobleTwo;
    int strength;
    vector<Noble*> nobles;
    vector<Warrior*> allWarriors;
    vector<Warrior*> unemployed;
    
    while (war >> action){
        
        //creates a new noble with his name and adds distinct noble pointer to a vector of nobles
        if (action == "Noble"){
            war >> nobleOne;
            Noble* noble = new Noble(nobleOne);
            nobles.push_back(noble);

        }
        
        //creates a new warrior with his name and strength and adds distinct warrior pointer to a vector of all warriors
        if (action == "Warrior"){
            war >> warrior >> strength;
            Warrior* aWarrior = new Warrior(warrior, strength);
            allWarriors.push_back(aWarrior);

        }
        
        //hires warriors into a noble's army
        if (action == "Hire"){
            war >> nobleOne >> warrior;
            for (size_t n = 0; n < nobles.size(); n++){
                for (size_t w = 0; w < allWarriors.size(); w++){
                    if (nobles[n]->getName() == nobleOne && allWarriors[w]->getName() == warrior){
                        nobles[n]->hire(*allWarriors[w]);
                    }
                }
            }
        }
        
        //fires warriors from a noble's army
        if (action == "Fire") {
            war >> nobleOne >> warrior;
            for (Noble* noble:nobles) {
                for (Warrior* warri:allWarriors) {
                    if (noble->getName() == nobleOne && warri->getName() == warrior){
                        noble->fire(*warri);
                        unemployed.push_back(warri);
                    }
                }
            }
        }
        
        //displays warriors
        else if (action == "Status"){
            cout << "Status\n======" << endl;
            cout << "Nobles:" << endl;
            if (nobles.size() > 0) {
                for (int i = 0; i < nobles.size(); i++) {
                    nobles[i]->display();
                }
            }
            else {
                cout << "NONE" << endl;
            }

            cout << "Unemployed Warriors:" << endl;
            if (unemployed.size() == 0) {
                cout << "NONE" << endl;
            }
            else {
                for (int u = 0; u < unemployed.size(); u++) {
                    unemployed[u]->display();
                }
            }
        }
        
        //battles warriors
        else if (action == "Battle"){
            war >> nobleOne >> nobleTwo;
            for (Noble* nobOne:nobles){
                for (Noble* nobTwo:nobles){
                    if (nobleOne == nobOne->getName() && nobleTwo == nobTwo->getName()) {
                        nobOne->battle(*nobTwo);
                    }
                }
            }
        }
        
        else if (action == "Clear"){
            for (size_t n = 0; n < nobles.size(); n++) {
                nobles[n]->reset();
                nobles[n] = NULL;
                delete nobles[n];

            }
            nobles.clear();
            for (size_t w = 0; w < allWarriors.size(); w++) {
                allWarriors[w] = NULL;
                delete allWarriors[w];
                
            }
            allWarriors.clear();
            for (size_t u = 0; u < unemployed.size(); u++) {
                unemployed[u] = NULL;
                delete unemployed[u];
            }
            unemployed.clear();
        }
    }
}

int main() {
    
    ifstream war("nobleWarriors.txt");
    if (!war) {
        cerr << "this is an incorrect file.";
        exit(1);
    }
    
    readFile(war);

    return 0;
}
