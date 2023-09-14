#include "printImage.h"
#include <vector>
#include <fstream>


void printImage(std::string imageFile) {
    std::ifstream ifs(imageFile);
    std::vector<std::string> out;
    if(!ifs.is_open()) return;
    while(!ifs.eof()) {
        std::string temp;
        getline(ifs,temp);
        out.push_back(temp);
    }
    for(auto s:out) std::cout << s << '\n';
}
