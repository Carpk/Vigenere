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
const int PHRASESIZE = 81;
const int WORDSIZE = 17;


void choicesPrompt() {
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
}



void dictCount() {
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

void encodeText(char toEncode[81], char keyword[17]) {
    int eChar;
    int keyLen = strlen(keyword);

    for (unsigned i = 0; i < strlen(toEncode); i++) {
        if ((toEncode[i] >= 'a') && (toEncode[i] <= 'z')) { //96, and 123
            eChar = 97 + ((toEncode[i] + keyword[i % keyLen]) - 194) % 26;
            toEncode[i] = eChar;
        }
    }
    //return toEncode;
}

void encodeTextReporting(char toEncode[81], char keyword[17]){
    cout << "Keyword, plainText and ciphertext are:  \n";
    for (int i = 0; i < strlen(toEncode); i++) {cout << keyword[i % strlen(keyword)];}

    cout << "\n" << toEncode << "\n";
    encodeText(toEncode, keyword);
    cout << toEncode << endl;
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
    menuOption = 2;

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
            strcpy(output, "all generalizations are false");
            cout << "Enter a keyword for Vigenere encryption: ";
            //cin >> keyword;
            strcpy(keyword , "secret");

            encodeTextReporting(output, keyword);
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

