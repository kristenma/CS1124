//
//  submission: hw05.cpp
//  programmer: kristen ma
//  n19680951
//  knm316
//
//  this program takes a hierarchy of nobles, lords, nobles who fight, protectors, wizards, warriors, archers, and swordsmen. nobles can only battle other nobles. however, lords have armies of protectors and nobles who fight have the ability to battle other armies for themselves, using their own strength. when the strength of one noble is greater than that of the other noble, the noble and its respective army (if it has one) of lesser strength die and the strength of the noble who is still standing loses a fraction of his strength due to battle.

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Protector {
public:
    // constructor initializes data and includes a status to check if protector is already hired or not to keep others from hiring
    Protector(const string& aName, double strength) : name(aName), strength(strength), hireStatus(false), aliveStatus(true) {}
    
    virtual void display() const = 0;
    
    void setStrength(int newStrength) {
        strength = newStrength;
    }
    
    string getName() const{
        return name;
    }
    
    double getStrength() const{
        return strength;
    }
    void setHireStatus(bool status) {
        hireStatus = status;
    }
    
    bool getStatus() const{
        return hireStatus;
    }
    
    void setBoss(string boss) {
        bossName = boss;
    }
    
    string getBossName() const{
        return bossName;
    }
private:
    const string name;
    string bossName;
    double strength;
    bool hireStatus;
    bool aliveStatus;
    
};


class Warrior : public Protector{
public:
    //constructor initializes abstract warrior name and strength as a protector derived class
    Warrior(string name, double strength) : Protector(name, strength) {}
    
    virtual void display() const{
        cout << this->getName() << " says: " << "Take that in the name of my lord, " << getBossName() << endl;
    }
};


class Swordsman : public Warrior {
public:
    //constructor initializes swordsman name and strength as a warrior derived class
    Swordsman(string name, double strength) : Warrior(name, strength) {}
    
    void display() const{
        cout << "CLANG! ";
        Warrior::display();
    }
};


class Archer : public Warrior {
public:
    //constructor initializes archer name and strength as a warrior derived class
    Archer(string name, double strength) : Warrior(name, strength) {}
    
    void display() const{
        cout << "TWANG! ";
        Warrior::display();
    }
};


class Wizard : public Protector{
public:
    //constructor initializes wizard name and strength as a protector derived class
    Wizard(string name, double strength) : Protector(name, strength) {}
    
    void display() const{
        cout << "POOF!" << endl;
    }
};


class Noble {
public:
    //constructor initializes NAME ONLY for nobles; strengths differ between noble derived classes; initializes for liveliness of noble as well
    Noble(const string& aName) : name(aName), alive(true) {}
    
    //winner of battle reduces strength by ratio of battler strengths
    virtual void warEffect(double warRatio) = 0;
    
    //obtaining of strengths differ between kinds of nobles
    virtual double getTotalStrength() const = 0;
    
    virtual void display() const = 0;
    
    string getName() const {return name;}
    
    bool getHealth() const {return alive;}
    
    virtual void deathOfNoble() {this->alive = false;}
    
    //nobles can only battle each other; method produces outcomes of battle depending on strengths
    void battle(Noble& aNoble) {
        cout << this->name << " battles " << aNoble.getName() << endl;
        
        //if first noble strength is greater than opposing strength
        if (this->getTotalStrength() > aNoble.getTotalStrength()){
            if (aNoble.alive == false){
                cout << "He's dead, " << this->name << endl;
            }
            
            else{
                this->warEffect(aNoble.getTotalStrength() / this->getTotalStrength());
                this->display();
                aNoble.deathOfNoble();
                cout << this->name << " defeats " << aNoble.getName() << endl;
            }
            
        }
        
        //if first noble strength is less than opposing strength
        else if (this->getTotalStrength() < aNoble.getTotalStrength()){
            if (this->alive == false){
                cout << "He's dead, " << aNoble.getName() << endl;
            }
            
            else{
                aNoble.warEffect(this->getTotalStrength() / aNoble.getTotalStrength());
                this->display();
                this->deathOfNoble();
                cout << aNoble.getName() << " defeats " << this->name << endl;
            }
        }
        
        //if strengths are equal!
        else if (this->getTotalStrength() == aNoble.getTotalStrength()){
            if (this->alive == false && aNoble.alive == false){
                cout << "Oh, NO! They're both dead!  Yuck!" << endl << endl;
            }
            else{
                this->deathOfNoble();
                this->display();
                aNoble.deathOfNoble();
                cout << "Mutual Annihalation:  " << this->name << " and "
                << aNoble.getName() << " die at each others hand" << endl;
            }
        }
    }
    
private:
    const string name;
    bool alive;
};


class Lord : public Noble{
public:
    //constructor initializes name as abstract noble
    Lord(string name) : Noble(name){}
    
    void display() const{
        for (size_t i = 0; i < defenders.size(); i++){
            defenders[i]->display();
        }
    }
    void deathOfNoble() {
        for (size_t j = 0; j < defenders.size(); j++){
            this->defenders[j]->setStrength(0);
        }
        Noble::deathOfNoble();
    }
    
    void warEffect(double warRatio){
        for (size_t k = 0; k < this->defenders.size(); k++){
            double currentStrength = this->defenders[k]->getStrength();
            this->defenders[k]->setStrength(currentStrength - (currentStrength * warRatio));
        }
    }
    
    double getTotalStrength() const{
        double totalStrength = 0;
        for (size_t l = 0; l < defenders.size(); l++){
            totalStrength += defenders[l]->getStrength();
        }
        
        return totalStrength;
    }
    
    //ensures noble is alive and warrior is not already in another army before hiring
    void hires(Protector& aProtector) {
        if (this->getHealth() == true && aProtector.getStatus() == false){
            aProtector.setHireStatus(true);
            aProtector.setBoss(getName());
            defenders.push_back(&aProtector);
        }
        else{
            // otherwise nothing happens when a dead noble tries to hire or a warrior is already hired
        }
    }
    
    // removes protector from army and moves everyone back by one to keep the order and to pop back
    void fire(Protector& aProtector) {
        if (this->getHealth() == true && aProtector.getStatus() == true){
            for (size_t m = 0; m < defenders.size(); m++) {
                if (&aProtector == defenders[m]) {
                    if (m < defenders.size() - 1) {
                        for (size_t n = m; n < defenders.size() - 1; n++) {
                            defenders[n] = defenders[n + 1];
                        }
                    }
                }
            }
            
            cout << "You don't work for me any more " << aProtector.getName() << "!   --" << this->getName() << endl << endl;
            defenders.pop_back();
            aProtector.setHireStatus(false);
        }
    }
    
private:
    vector<Protector*> defenders;
};

class PersonWithStrengthToFight : public Noble {
    
public:
    PersonWithStrengthToFight(string name, double power) : Noble(name), strength(power){}
    
    void display() const {/* these people don't say anything when they fight */}
    double getTotalStrength() const{ return strength; }
    void warEffect(double warRatio){ this -> strength = (strength - (strength * warRatio)); }
    void deathOfNoble() {
        this->strength = 0;
        Noble::deathOfNoble();
    }
    
private: 
    double strength;
};

int main(){
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
    
    system("pause");
    
}
