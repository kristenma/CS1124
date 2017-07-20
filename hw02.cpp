//
//  submission: hw02.cpp
//  programmer: kristen ma
//  n19680951
//  knm316
//
//  This program takes a file of warriors and reads through it according to the commands. When a warrior is read, he is put into a class with his name, his weapon's name, and its respective strength. They are listed out initially before battle to determine the initial strengths. Then, the warriors are put to battle with each other. Stronger warriors survive, weaker warriors die, and those whose weapons have the same strength die together. Then, each warrior is listed out once again with the weapon's respective strengths following battles.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//class contains a name and strength
class Weapon {
public:
    Weapon(string n, int s) : weaponName(n), strength(s){
        //name = n;
        //strength = s;
    }
    
    void display(ostream& os)const{
        os << weaponName << " , " << strength;
    }
    
    int getStrength()const{
        return strength;
    }
    
    string getName()const{
        return weaponName;
    }

private:
    string weaponName;
    int strength;
};

//class contains a name and weapon
class Warrior {
public:
    Warrior(const string& n, string w, int s) : name(n), weapon(w), strength(s){
        // name = warriorName
    }
    
    string getName()const{
        return name;
    }
    
    string getWeapon()const{
        return weapon;
    }
    
    int getStrength()const{
        return strength;
    }
    
    void setStrength(int s){
        strength = s;
    }
    
private:
    string name;
    string weapon;
    int strength;
};

//lists out warrior information including name and strength
void displayWarriorInfo(vector<Warrior>& warriors){
    size_t sizeOfVector = warriors.size();
    cout << "There are " << sizeOfVector << " warriors." << endl;
    for (int i=0; i < warriors.size(); i++) {
        
        //declares variables for Class info
        string warriorName;
        string weaponName;
        int weaponStrength;
        warriorName = warriors[i].getName();
        weaponName = warriors[i].getWeapon();
        weaponStrength = warriors[i].getStrength();
        
        cout << "Warrior: " << warriorName << " | Weapon: " << weaponName << ", " << weaponStrength << endl;
    }
}

//compares warrior strengths to each other before deciding who wins and who dies
void displayBattles(string& warriorOne, string warriorTwo, vector<Warrior>& warriors){
    cout << warriorOne << " battles " << warriorTwo << "." << endl;
    
    //takes index of list of warriors
    for (int i=0; i < warriors.size(); i++) {
        for (int j=0; j < warriors.size(); j++) {
            
            //declare variables for accessor functions from Warrior Class
            string nameOne;
            string nameTwo;
            int weaponOneStrength;
            int weaponTwoStrength;
            nameOne = warriors[i].getName();
            nameTwo = warriors[j].getName();
            weaponOneStrength = warriors[i].getStrength();
            weaponTwoStrength = warriors[j].getStrength();
            
            //if the names from the file match the names in the list of warriors, compare strengths
            if (warriorOne == nameOne && warriorTwo == nameTwo){
                if (weaponOneStrength > weaponTwoStrength) {
                    if (weaponTwoStrength == 0){
                        cout << "He's dead, " << nameOne << "." << endl;
                    }
                    else {
                        cout << nameOne << " defeats " << nameTwo << "." << endl;
                        warriors[i].setStrength(weaponOneStrength - weaponTwoStrength);
                        warriors[j].setStrength(0);
                    }
                }
                else if (weaponOneStrength < weaponTwoStrength) {
                    if (weaponOneStrength == 0){
                        cout << "He's dead, " << nameTwo << "." << endl;
                    }
                    else {
                        cout << nameTwo << " defeats " << nameOne << "." << endl;
                        warriors[j].setStrength(weaponTwoStrength - weaponOneStrength);
                        warriors[i].setStrength(0);
                    }
                }
                else if (weaponOneStrength == weaponTwoStrength){
                    if (weaponOneStrength == 0 && weaponTwoStrength == 0){
                        cout << "Oh, NO! They're both dead! Yuck!" << endl;
                    }
                    else{
                        cout << "Mutual Annihilation: " << nameOne << " and " << nameTwo << " die in each other's hands." << endl;
                        warriors[i].setStrength(0);
                        warriors[j].setStrength(0);
                    }
                }
            }
        }
    }
    
}

//reads through the warrior file and acts accordingly
void readFile(ifstream& warriorFile, vector<Warrior> warriors){
    string action;
    string warriorOne;
    string warriorTwo;
    string weaponName;
    int weaponStrength;
    
    while (warriorFile >> action){
        
        //creates a new warrior struct with his name and strength and adds distinct struct to a vector of warriors
        if (action == "Warrior"){
            warriorFile >> warriorOne >> weaponName >> weaponStrength;
            Warrior warriorInfo(warriorOne, weaponName, weaponStrength);
            warriors.push_back(warriorInfo);
        }
        
        //displays warriors
        else if (action == "Status"){
            displayWarriorInfo(warriors);
        }
        
        //battles warriors
        else if (action == "Battle"){
            warriorFile >> warriorOne >> warriorTwo;
            displayBattles(warriorOne, warriorTwo, warriors);
            
        }
    }
}

int main() {
    //opens file and checks for accuracy
    ifstream warriorFile("warriors.txt");
    if (!warriorFile) {
        cerr << "This is an incorrect file.";
        exit(1);
    }
    
    //creates a vector of warriors
    vector<Warrior> warriors;
    
    readFile(warriorFile, warriors);
    
    warriorFile.close();
    system("pause");
    
    return 0;
}
