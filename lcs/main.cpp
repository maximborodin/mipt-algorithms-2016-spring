#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctime>
#include "advancedAlgorithm.h"
#include "trivialAlgorithm.h"


void stringsGen (std::string& str1, std::string& str2, unsigned int len1,
                unsigned int len2, unsigned int alphabetSize)
{
    str1.resize(len1);
    str2.resize(len2);
    for (int j = 0;j < len1;j++){
        str1[j] = static_cast<char>(rand() % alphabetSize) + 'a';
    }
    for (int j = 0;j < len2;j++){
        str2[j] = static_cast<char>(rand() % alphabetSize) + 'a';
    }
}

bool checkAnswers (std::vector<std::vector<unsigned int> >& ans1,
                   std::vector<std::vector<unsigned int> >& ans2)
{
    if (ans1.size() != ans2.size()) {
        return false;
    }
    for (size_t i = 0;i < ans1.size();i++){
        if (ans1[i].size() != ans2[i].size()){
            return false;
        }
        for (size_t j = 0;j < ans1[i].size();j++){
            if (ans1[i][j] != ans2[i][j]){
                return false;
            }
        }
    }
    return true;
}


void check (unsigned int testsCount, unsigned int alphabetSize)
{
    alphabetSize = std::min (static_cast<int>(alphabetSize), 26);
    for (int i = 0;i < testsCount;i++){
        std::string str1, str2;
        int len1 = rand() % 501; // по-хорошему, следует установить % 2001, но тогда
        int len2 = rand() % 501; // trivial algorithm работает довольно долго(
        stringsGen (str1, str2, len1, len2, alphabetSize);
        std::vector<std::vector<unsigned int> > ans1, ans2;
        ans1 = calculateSuffixPrefixLCS(str1, str2);
        ans2 = trivialCalculate(str1, str2);
        if (len1 > 50 || len2 > 50) {
            std::cout << "Large test" << std::endl;
        }
        else {
            std::cout << "Small test: " << std::endl;
            std::cout << "  String1: " << str1 << std::endl;
            std::cout << "  String2: " << str2 << std::endl;
        }
        if (checkAnswers(ans1, ans2)){
            std::cout << "Test #" << i << " checked successful" << std::endl;
        }
        else{
            std::cout << "Test #" << i << " something went wrong" << std::endl;
            return;
        }
    }
    std::cout << "LCS works right" << std::endl;
}

int main()
{
    srand(time(NULL));
    check(30, 26);
    return 0;
}