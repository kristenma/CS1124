//
//  programmer: kristen ma
//  university id: N19680951
//  net id: knm316
//  assignment: hw00.cpp
//
//  this program opens and reads a file with encrypted characters in it and uses the provided rotational integer to decrypt the file. after the file is decrypted, this program reverses the lines and prints the file out in the correct order.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// obtains the encrypted character and returns the decrypted character using the rotational integer
char decryptChar(char encryptedChar, int rotation) {
    
    //ascii character numbers for lowercase is between 97 and 122
    //if ascii character isnt between these two numbers, do nothing
    if (encryptedChar >= 'a' && encryptedChar <= 'z') {
        
        // if ascii character is out of range of lowercase letters, wrap around back to end of alphabet
        if ((encryptedChar - rotation) < 'a') {
            
            encryptedChar = char(encryptedChar + 26);
        }
        
        //takes encryptedChar and decrpyts it by rotating the character using the rotation variable
        else {
            encryptedChar = encryptedChar - rotation;
        }
    }
    return encryptedChar;
}

// takes encrypted line and decrypts the line for each character
void decryptedString(string& encryptedLine, const int& rotation, vector<string>& decrypted) {
    
    //goes through the line and decrypts it by character
    for (int i = 0; i < encryptedLine.size(); i++) {
        if (encryptedLine[i] != ' ' && encryptedLine[i] != '\n' && encryptedLine[i] != '.') {
            encryptedLine[i] = decryptChar(encryptedLine[i], rotation);
        }
    }
    
    //adds the decrypted line onto the string vector decrypted
    decrypted.push_back(encryptedLine);
}


int main() {
    //opens and checks if file exists or not
    ifstream encrypted("encrypted.txt");
    
    if (!encrypted){
        cerr << "This is an incorrect file.\n";
        exit(1);
    }
    
    //reads first integer of file as the rotational number used to decrypt the text
    int rotation;
    encrypted>>rotation;
    
    //gets empty string line
    string encryptedLine;
    getline(encrypted,encryptedLine);
    
    //creates a vector of strings called decrypted
    vector<string> decrypted;
    
    //goes through the file and replaces the encryptedLine string with encrypted lines to be decrypted
    while (getline(encrypted, encryptedLine)){
        decryptedString(encryptedLine, rotation, decrypted);
    }
    
    //displays decryption
    //for every decrypted object in the vector, this will print it out
    
    for (string& encryptedLine : decrypted){
        decryptedString(encryptedLine, rotation, decrypted);
    }
    for (int i = decrypted.size() - 1; i >= 0; i--){
        cout << decrypted[i] << endl;
    }
    
    encrypted.close();
    system ("pause");
    return 0;
}
