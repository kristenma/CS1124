//
//  submission: hw01.cpp
//  programmer: kristen ma
//  n19680951
//  knm316
//
//  This program takes a file of warriors and reads through it according to the commands. When a warrior is read, he is put into a struct with his name and his respective strength. They are listed out initially before battle to determine the initial strengths. Then, the warriors are put to battle with each other. Stronger warriors survive, weaker warriors die, and those with the same strength die together. Then, each warrior is listed out once again with the respective strengths following battles.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//contains a name and strength
struct Warrior {
    string name;
    int strength;
};

//lists out warrior information including name and strength
void displayWarriorInfo(vector<Warrior>& warriors){
    size_t sizeOfVector = warriors.size();
    cout << "There are " << sizeOfVector << " warriors." << endl;
    for (int i=0; i < warriors.size(); i++) {
        cout << "Warrior: " << warriors[i].name << ", Strength: " << warriors[i].strength << endl;
    }
}

//compares warrior strengths to each other before deciding who wins and who dies
void displayBattles(string& warriorOne, string warriorTwo, vector<Warrior>& warriors){
    cout << warriorOne << " battles " << warriorTwo << "." << endl;
    //takes index of list of warriors
    for (int i=0; i < warriors.size(); i++) {
        for (int j=0; j < warriors.size(); j++) {
            //if the names from the file match the names in the list of warriors, compare strengths
            if (warriorOne == warriors[i].name && warriorTwo == warriors[j].name){
                if (warriors[i].strength > warriors[j].strength) {
                    if (warriors[j].strength == 0){
                        cout << "He's dead, " << warriors[i].name << "." << endl;
                    }
                    else {
                        cout << warriors[i].name << " defeats " << warriors[j].name << "." << endl;
                        warriors[i].strength = warriors[i].strength - warriors[j].strength;
                        warriors[j].strength = 0;
                    }
                }
                else if (warriors[i].strength < warriors[j].strength) {
                    if (warriors[i].strength == 0){
                        cout << "He's dead, " << warriors[j].name << "." << endl;
                    }
                    else {
                        cout << warriors[j].name << " defeats " << warriors[i].name << "." << endl;
                        warriors[j].strength = warriors[j].strength - warriors[i].strength;
                        warriors[i].strength = 0;
                    }
                }
                else if (warriors[i].strength == warriors[j].strength){
                    if (warriors[i].strength == 0 && warriors[j].strength == 0){
                        cout << "Oh, NO! They're both dead! Yuck!" << endl;
                    }
                    else{
                    cout << "Mutual Annihilation: " << warriors[i].name << " and " << warriors[j].name << " die in each other's hands." << endl;
                    warriors[i].strength = 0;
                    warriors[j].strength = 0;
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
    int warriorStrength;
    
    while (warriorFile >> action){
        
        //creates a new warrior struct with his name and strength and adds distinct struct to a vector of warriors
        if (action == "Warrior"){
            warriorFile >> warriorOne >> warriorStrength;
            Warrior warriorInfo;
            warriorInfo.name = warriorOne;
            warriorInfo.strength = warriorStrength;
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
