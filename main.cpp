/*----------------------------------------------------------
 * Program 2: Vigenere
 *
 * Class: CS 141, Spring 2020. Tue 4pm lab
 * System: CLion on Windows 10 & CLion on Mac
 * Author: Shawn Klein
 * ---------------------------------------------------------
 */

#include <iostream>
#include<fstream>
#include <cctype>
using namespace std;

cout << "Choose from the following options: \n"
<< "    1. Lookup dictionary word \n"
<< "    2. Encode some text  \n"
<< "    3. Decode some text  \n"
<< "    4. Auto-decode the ciphertext given with the assignment  \n"
<< "    5. Exit program  \n"
<< "Your choice: ";
cin >> menuOption;
returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
// This is necessary because otherwise a subsequent cin.getline() reads it as
// an empty line of input.
switch( menuOption) {
case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
cout << "Enter a word to be looked up in dictionary: ";

break;

case 2: // Encode some text
cout << "Enter the text to be encoded: ";

cout << "Enter a keyword for Vigenere encryption: ";

cout << "Keyword, plainText and ciphertext are:  \n";

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
// Sanity check
cout << "Invalid menu option.  Exiting program." << endl;
break;
}

int main() {
    int menuOption;
    char returnCharacter;

    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
    cin >> menuOption;
    returnCharacter = cin.get();

    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            break;
        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            cout << "Enter a keyword for Vigenere encryption: ";
            cout << "Keyword, plainText and ciphertext are:  \n";
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
