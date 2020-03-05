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
#include <sstream>

using namespace std;

const int DICTSIZE = 21800;
const int WORDSIZE = 17;
const int PHRASESIZE = 81;

void choicesPrompt() {
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
}

string sanitizeText(string str) {
    //str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    return str;
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



bool binarySearchDict(char dictArray[21800][17], char word[81]) {
    int low, mid, high;
    bool isFound = false;
    low = 0;
    high = 21800-1;
    while ( low <= high) {
        mid = (low + high) / 2;
        if (strcmp(word, dictArray[mid]) == 0) {
            isFound = true;
            break;
        }
        else if (strcmp(word, dictArray[mid]) < 0){
            high = mid -1;
        } else {
            low = mid + 1;
        }
    }

    return isFound;
}

string encodeText(string toEncode, string keyword) {
    int eChar;
    int keyLen = keyword.size();

    for (unsigned i = 0; i < toEncode.size(); i++) {
        //int toEncChar = toEncode[i];
        if ((toEncode[i] >= 'a') && (toEncode[i] <= 'z')) { //96, and 123
            eChar = 97 + ((toEncode[i] + keyword[i % keyLen]) - 194) % 26;
            toEncode[i] = eChar;
        }
    }
    return toEncode;
}

void encodeTextReporting(char toEncode[81],char keyword[17]){
    //toEncode = sanitizeText(output);
    cout << "Keyword, plainText and ciphertext are:  \n";
    for (unsigned i = 0; i < strlen(toEncode); i++) {cout << keyword[i % strlen(keyword)];}
    cout << "\n" << toEncode << "\n" << encodeText(toEncode, keyword) << endl;
}

string decodeText(char toDecode[81], char keyword[]) {
    int eChar;
    int keyLen = strlen(keyword);
    //cout << "decoding: " << toDecode << " with " << keyword << endl;
    for (unsigned i = 0; i < strlen(toDecode); i++) {
        if ((toDecode[i] > 64) && (toDecode[i] < 123)) {
            int decodeChar = tolower(toDecode[i]);
            int keywordChar = tolower(keyword[i % keyLen]);

            if (keywordChar > decodeChar) {
                eChar = 'z' - keywordChar + decodeChar + 1;
            } else {
                eChar = 'a' + (decodeChar - keywordChar);
            }

            toDecode[i] = eChar;
        }
    }
    return toDecode;
}

void decodeTextReporting(char dictArray[DICTSIZE][WORDSIZE], char toDecode[], char keyword[]) {
    int validWordCount = 0;
    char decodedWord[17];
    //char decodedText[81] = decodeText(toDecode, keyword);
    stringstream decodedStream(decodeText(toDecode, keyword));
    while (decodedStream >> decodedWord) {
        decodedWord[strlen(decodedWord)] = '\0';
        if (binarySearchDict(dictArray, decodedWord)) {validWordCount++;}
    }
    cout << validWordCount << " words found using keyword: " << keyword << " giving:" << endl;
    cout << decodeText(toDecode, keyword) << endl;
}

void loadDict(char dictArray[21800][17]) {
    ifstream inStream;
    inStream.open( "dictionary.txt");
    if( !inStream.is_open()) {cout << "Could not find dictionary.txt.  Exiting..." << endl; exit( -1);}
    int i = 0;

    char dictWord[81];
    while( inStream >> dictWord) {
        //if (dictWord.at(dictWord.size()-1) < 97 ) { dictWord.replace(dictWord.size()-1, 1,"" ); }
        if (strlen(dictWord) >= 3) {
            for (int j = 0; j < strlen(dictWord); j++ ) {
                dictWord[j] = tolower(dictWord[j]);
            }
            dictWord[strlen(dictWord)] = '\0';

            strcpy(dictArray[i], dictWord);
            i++;
        }
    }
    inStream.close();
}


string autoDecode(char dictArray[21800][17], const char text[81]) {
    int bestWordCount = 1;
    string bestDecodedText;
    char possibleKey[17];
    string possibleDecodedText;
    char tempText[81];

    ifstream codeBook("TheSecretAgentByJosephConrad.txt");
    for (string line; getline(codeBook, line);) {
        stringstream codeBookStream(line);

        while (codeBookStream >> possibleKey) {
            char decodedWord[17];
            int validWordCount = 0;
            //possibleKey = sanitizeText(possibleKey);
            for (int j = 0; j < strlen(possibleKey); j++ ) {
                possibleKey[j] = tolower(possibleKey[j]);
            }
            possibleKey[strlen(possibleKey)] = '\0';

            strcpy(tempText, text);
            possibleDecodedText = decodeText(tempText, possibleKey);

            stringstream decodedStream(possibleDecodedText);
            while (decodedStream >> decodedWord) {
                decodedWord[strlen(decodedWord)] = '\0';
                //cout << decodedWord << endl;
                if (binarySearchDict(dictArray, decodedWord)) {validWordCount++;}
            }

            if (validWordCount >= bestWordCount) {
                bestWordCount = validWordCount;
                bestDecodedText = possibleDecodedText;
                cout << validWordCount << " words found using keyword: " << possibleKey << " giving:" << endl;
                cout << possibleDecodedText << endl;
            }

        }
    }
}



int main() {
    int menuOption = 0;
    char returnCharacter;
    char dictArray[21800][17];
    loadDict(dictArray);
    string userInput;
    string toEncode;
    char toDecode[81] = "uev os hnocax xia lxn\0";
    string decodedText;
    char keyword[17];
    char output[100];

    //strlen(dictArray);
    dictCount();

    //choicesPrompt();
    //cin >> menuOption;
    //returnCharacter =
    //cin.get(output,100);
    menuOption = 1;

    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            //cin.get(output,100);
            //strcpy(output, "kats");
            strcpy(output, "procrastinate");
            cout << output << (binarySearchDict(dictArray,output)? " IS ":" is NOT ")  << "in the dictionary." << endl;
            //cout << output << (dictLookup(output)? " IS ":" is NOT ")  << "in the dictionary." << endl;
            break;
        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            //cin.get(output,100);
            toEncode = "all generalizations are false";
            cout << "Enter a keyword for Vigenere encryption: ";
            //cin >> keyword;
            strcpy(keyword , "secret");
            toEncode = sanitizeText(toEncode);
            cout << "Keyword, plainText and ciphertext are:  \n";
            for (unsigned i = 0; i < toEncode.size(); i++) {cout << keyword[i%6];}
            cout << endl << toEncode << "\n" << encodeText(toEncode, keyword) << endl;
            break;
        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            //toDecode = "spn kxfitrpbrevzsgk cii xenji";
            cout << "Enter a Vigenere keyword to be tried: ";
            strcpy(keyword , "secret");
            cout << endl;

            decodeTextReporting(dictArray, output, keyword);
            break;
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";

            autoDecode(dictArray, toDecode);

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
 *
 *
int validWordCount(string text) {
    string word;
    int validCount = 0;
    stringstream iss(text);
    while (iss >> word) {
        if (dictLookup(word)) {
            validCount++;
        }
    }

    return validCount;
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





 //cout << "j: " << int('j') << " r: " << int('r') << " n: " << int('n') << " z: " << int('z') << endl;


 eChar = 97 + ((toDecode[i] - keyword[i % keyLen]));
            if (eChar < 97) {
                //eChar = 97 + (keyword[i % keyLen] - toDecode[i]);
                //int shiftKey = toDecode[i] - 'a';
                //eChar = 97 + ((toDecode[i] - keyword[i % keyLen])) + shiftKey;
                //cout << "char: " << char(eChar) << eChar << " shift: " << shiftKey << endl;
            }




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