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
    for (unsigned i = 0; i < str.size(); i++) {
        if ((str[i] < 97) | (str[i] > 122)) {
            str[i] = ' ';
        }
    }
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
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

string encodeText(string toEncode, string keyword) {
    int eChar;
    int keyLen = keyword.size();

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

string decodeText(string toDecode, string keyword) {
    int eChar;
    int keyLen = keyword.size();

    for (unsigned i = 0; i < toDecode.size(); i++) {
        if ((toDecode[i] > 64) && (toDecode[i] < 123)) {
            int decodeChar = tolower(toDecode[i]);
            int keywordChar = tolower(keyword[i % keyLen]);

            if (keywordChar > decodeChar) {
                eChar = 'z' - keywordChar + decodeChar + 1;
            } else {
                eChar = 97 + (decodeChar - keywordChar);
            }

            toDecode[i] = eChar;
        }
    }
    return toDecode;
}


void loadDict(char* dictArray[21800][81]) {
    ifstream inStream;
    char ndictArray[10000][81];
    int i = 0;
    inStream.open( "dictionary.txt");
    if( !inStream.is_open()) {cout << "Could not find dictionary.txt.  Exiting..." << endl; exit( -1);}

    string dictWord;
    while( inStream >> dictWord) {
        //dictWord.c_str() >> (ndictArray)[i];
        //(*dictArray)[i] = dictWord;
        strcpy(ndictArray[i], dictWord.c_str());
        i++;
    }
    cout << "in array: " << (*dictArray)[18437] << endl;
    inStream.close();
}



bool binarySearchDict(basic_string<char> *dictArray, string word) {
    int low, mid, high;
    cout << "in array: " << dictArray[18437] << endl;

    return false;
}


string autoDecode(string text) {
    int lineNum = 0;
    int bestWordCount = 1;
    string bestDecodedText;
    string possibleKey;
    string decodedText;

    char dictArray[21800][81];
    loadDict(&dictArray);
    //cout << "IM IN AUTODECODE" << endl;
    cout << "in array: " << dictArray[18437] << endl;

    ifstream nomenclator("TheSecretAgentByJosephConrad.txt");
    for (string line; getline(nomenclator, line);) {
        stringstream lineStream(line);

        while (lineStream >> possibleKey) {
            //possibleKey = sanitizeText(possibleKey);
            decodedText = decodeText(text, possibleKey);
            string decodedWord;
            int validWordCount = 0;
            stringstream decodedStream(decodedText);
            while (decodedStream >> decodedWord) {
                //if (binarySearchDict(dictArray, decodedWord)) {validWordCount++;}
                if (dictLookup(decodedWord)) {validWordCount++;}
            }

            if (validWordCount >= bestWordCount) {
                bestWordCount = validWordCount;
                bestDecodedText = decodedText;
                cout << validWordCount << " words found using keyword: " << possibleKey << " giving:" << endl;
                cout << decodedText << endl;
            }

        }
        if (++lineNum % 200 == 0) {cout << lineNum << endl;}
    }

}



int main() {
    int menuOption = 0;
    char returnCharacter;
    string userInput;
    string toEncode;
    string toDecode;
    string decodedText;
    string keyword;
    char output[100]  = "procrastinate";

    dictCount();

    //choicesPrompt();
    //cin >> menuOption;
    //returnCharacter =
    //cin.get(output,100);
    menuOption = 4;

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
            toDecode = "spn kxfitrpbrevzsgk cii xenji";
            cout << "Enter a Vigenere keyword to be tried: ";
            keyword =  "secret";
            cout << endl;

            decodedText = decodeText(toDecode, keyword);
            cout << validWordCount(decodedText) << " found using keyword: " << keyword << " giving:" << endl;

            cout << decodedText << endl;
            break;
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            toDecode = "uev os hnocax xia lxn";
            //toDecode = "nol ycwh io ffpllhg uenmvi ihv qmdprlieg: zcfnd lfkt pqwayhz ib ofl.db/dgiaoy13";

            autoDecode(toDecode);

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