/*----------------------------------------------------------
 * Program 2: Vigenere
 *
 * Class: CS 141, Spring 2020. Tue 4pm lab
 * System: CLion on Windows 10 & CLion on Mac
 * Author: Shawn Klein
 * ---------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>


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


bool dictLookup(string str) {
    vector<string> book;
    ifstream dictFile("dictionary.txt");
    for (string line; getline(dictFile, line);) {
        book.push_back(line);
    }

    cout << "book size: " << book.size() << endl;
    cout << "it is " << (find(book.begin(), book.end(), str) != book.end()) << endl;
}

int main() {
    int menuOption = 0;
    char returnCharacter;
    vector<string> book;

    ifstream dictFile("../TheSecretAgentByJosephConrad.txt");

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
    char output[100];




    //choicesPrompt();
    //cin >> menuOption;
    //returnCharacter = cin.get();

    //test 1 #1
    string userSearch = "procrastinate";
    dictLookup(userSearch);

    //test 2 #1
    // kats
    // should return -> kats is NOT in the dictionary.

    //test 3
    //2
    //all generalizations are false
    //secret
    //returns -> spn kxfitrpbrevzsgk cii xenji




    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            cin >> userSearch;
            dictLookup(userSearch);
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
