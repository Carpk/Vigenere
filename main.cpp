/*----------------------------------------------------------
 * Program 2: Vigenere
 *
 * Class: CS 141, Spring 2020. Tue 4pm lab
 * System: CLion on Windows 10
 * Author: Shawn Klein
 * ---------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;


void choicesPrompt() {
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
}

int dictCount() {
    int wordCount = 0;
    ifstream dictFile("dictionary.txt");
    for (string line; getline(dictFile, line);) {
        if (line.at(line.size()-1) < 97 ) { line.replace(line.size()-1, 1,"" ); }
        if (line.size() >= 3) { wordCount++; }
    }
    cout << wordCount << " words of size >= 3 were read in from dictionary. "<<' '<<"\n" << endl << endl;
}

bool dictLookup(string str) {
    bool isFound = false;
    ifstream dictFile("dictionary.txt");
    //str.resize(remove_if(str.begin(), str.end(),[](char x){return !isalnum(x) && !isspace(x);})-str.begin());
    if (str.at(0) < 97 ) { str.replace(0, 1,"" ); }
    if (str.at(str.size()-1) < 97 ) { str.replace(str.size()-1, 1,"" ); }
    string line;

    for (line; getline(dictFile, line);) {
        line.erase(line.size() - 1);
        if (strcmp(line.c_str(), str.c_str()) == 0 ) {isFound = true; break;}
    }
    return isFound;
}



string encodeText(string toEncode, string keyword) {
    int eChar;
    int keyLen = 6;
    string decoded;
    for (unsigned i = 0; i < toEncode.size(); i++) {
        int toEncChar = toEncode[i];
        if ((toEncode[i] > 64) && (toEncode[i] < 123)) {
            eChar = 97 + ((toEncode[i] + keyword[i % keyLen]) - 194) % 26;
            toEncode[i] = eChar;
        } else {
            //toEncode[i] = ' ';
        }
    }
    return toEncode;
}

string sanitizeText(string str) {
    for (unsigned i = 0; i < str.size(); i++) {
        if ((str[i] < 97) | (str[i] > 122)) {
            str[i] = ' ';
        }
    }
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

int main() {
    int menuOption = 0;
    char returnCharacter;
    string userInput;
    string toEncode;
    string keyword;
    char output[100]  = "procrastinate";

    dictCount();

    //choicesPrompt();
    //cin >> menuOption;
    //returnCharacter =
    //cin.get(output,100);
    menuOption = 1;

   //cout << "A is: " << int('A') << endl;

    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            //cin >> userInput;
            //output[]  = "procrastinate"; // 13
            //cout << strlen(userInput.c_str());
            //userInput = "kats";
            cout << userInput << (dictLookup(output)? " IS ":" is NOT ")  << "in the dictionary." << endl;
            break;
        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            //cin.get(output,100);
            toEncode = "all generalizations are false";
            cout << "Enter a keyword for Vigenere encryption: ";
            //cin >> keyword;
            keyword =  "secret";
            toEncode = sanitizeText(toEncode);
            cout << "Keyword, plainText and ciphertext are:  \n";
            for (unsigned i = 0; i < toEncode.size(); i++) {cout << keyword[i%6];}
            cout << endl << toEncode << "\n" << encodeText(toEncode, keyword) << endl;
            break;
        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            cout << "Enter a Vigenere keyword to be tried: ";
            break;
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            break;
        case 5: // exit program
            cout << "Exiting program" << endl;
            exit( 0);
            break;
        default:
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
    }
    return 0;
}








/*

cout << toEncode[i] << " keyword modo: " << (toEncode[i] + keyword[i % keyLen]);
eChar = 97 + ((toEncode[i] + keyword[i % keyLen])-194) % 26;
cout <<' '<< eChar << ' ';
toEncode[i] = eChar;
cout << toEncode[i] << endl;







         if (line[0]=='p' & line[4]=='r' & line[12]=='e' ){
            cout << "found the word: " << line << " vlaue: " << strcmp(line.c_str(), str.c_str()) << endl;
        }








     //test 1 #1
    userInput = "procrastinate";
    //dictLookup(userSearch);
    cout << userInput << " is " << (dictLookup(userInput)? "":"not ")  << "in the dictionary." << endl;

    //test 2 #1
    userInput = "kats";
    //dictLookup(userSearch);
    cout << userInput << " is " << (dictLookup(userInput)? "":"NOT ")  << "in the dictionary." << endl;

    // should return -> kats is NOT in the dictionary.

    //test 3
    //2
    string toEncode = "all generalizations are false";
    string keyword =  "secret";
    string encoded = encodeText(toEncode, keyword);
    for (int i = 0; i < toEncode.size(); i++) {cout << keyword[i%6];}
    cout << endl;
    cout << encoded << endl;
    //           all generalizations are false
    //returns -> spn kxfitrpbrevzsgk cii xenji







*/

// a = 97;  s = 115; s = 115;
// l = 108; e = 101; p = 112;
// 97+((108+101)%97


//ifstream dictFile("../TheSecretAgentByJosephConrad.txt");

//for (string line; getline(dictFile, line);) {
//remove_if(line.begin (), line.end (), ispunct());

//remove_copy_if(text.begin(), text.end(), back_inserter(result), ptr_fun<int, int>(&std::ispunct);

//istringstream iss(line);
//cout << line << endl;
// string word;
// while(iss>>word){
// Need to remove puncuation marks

//cout << word << endl;
// book.push_back(word);
// }
// }
//cout << "book size: " << book.size() << endl;