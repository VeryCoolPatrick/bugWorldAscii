#include "textFormater.h"

using std::string;
using std::vector;

//Takes user input and returns a vector of strings ready to run
vector<string> inputCommandReady() {
    string input;
    getline(std::cin, input);
    return formatLine(input);
}

//cleans a single string and returns a vector of strings ready to run
vector<string> formatLine(string input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);    //Converts to lowercase
    
    for(int i = 0; input[i] != '\0'; i++) {             //Converts non-letters to spaces
        if(input[i] >= 'a' && input[i] <= 'z') continue;
        input[i] = ' ';
    }
    
    vector<string> output;
    auto stringPointer = strtok(&input[0], " ");    //Splits input into words with space deliminators
    while(stringPointer) {
        output.push_back(stringPointer);
        stringPointer = strtok(nullptr, " ");
    }
    
    for(auto i = output.begin(); i != output.end(); i++) {
        if(find(DUD_WORDS.begin(), DUD_WORDS.end(), *i) != DUD_WORDS.end()) { //Removes dud words
            output.erase(i);
            i--;
        }
        
        if(DOUBLE_WORDS.find(*i) != DOUBLE_WORDS.end()) {    //Combine double words
//            if(*(i + 1) == DOUBLE_WORDS.find(*i)->second) {
//                *i = DOUBLE_WORDS.find(*i)->first + " " + DOUBLE_WORDS.find(*i)->second;
//                output.erase(i + 1);
//            }
            auto doublesIt {DOUBLE_WORDS.find(*i)};
            while(doublesIt->first == *i) {
                if(*(i + 1) == doublesIt->second) {
                    *i = DOUBLE_WORDS.find(*i)->first + " " + DOUBLE_WORDS.find(*i)->second;
                    output.erase(i + 1);
                    break;
                }
                doublesIt++;
            }
        }
    }
    return output;
}

//Returns input string with first letter capitalised
string capitalise(string input) {
    input[0] = toupper(input[0]);
    return input;
}