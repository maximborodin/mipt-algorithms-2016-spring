//
// Created by maxim on 2/27/16.
//
/**/

#include "splayTree.h"
//#include "splayTree.cpp"
#include "stlRealize.h"
#include <fstream>
#include <ctime>
#include "permutationInterface.h"

bool algorithmChecker(MassiveI* massive, std::istream& in)
{
    STLRealize stlStruct;
    int queries;
    in >> queries;
    for(int i = 0;i < queries;i++){
        std::string command;
        in >> command;
        if (command == "add"){
            int l, r, val;
            in >> l >> r >> val;
            stlStruct.add (l, r, val);
            massive->add (l, r, val);
        }
        else if (command == "replace"){
            int ind, val;
            in >> ind >> val;
            stlStruct.replace (ind, val);
            massive->replace (ind, val);
        }
        else if (command == "sum"){
            int l, r;
            in >> l >> r;
            if (stlStruct.sum(l, r) != massive->sum(l, r)){
                return false;
            }
        }
        else if (command == "insert"){
            int ind, val;
            in >> ind >> val;
            stlStruct.insert (ind, val);
            massive->insert (ind, val);
        }
        else if (command == "nextPermutation"){
            int l, r;
            in >> l >> r;
            stlStruct.nextPermutation (l, r);
            massive->nextPermutation (l, r);
        }
        //std::vector<int> arr = massive->getMassive();
        //for (size_t i = 0;i < arr.size();i++){
        //    std::cout << arr[i] << " ";
        //}
        //std::cout << std::endl;
        //arr = massive->getMassive();
        //for (size_t i = 0;i < arr.size();i++){
        //   std::cout << arr[i] << " ";
        //}
        //std::cout << std::endl;
        if (stlStruct.getMassive() != massive->getMassive()){
            return false;
        }
    }
    if (stlStruct.getMassive() != massive->getMassive()){
        return false;
    }
    return true;
}

int main ()
{
    std::ifstream in;
    in.open ("test.txt", std::ifstream::in);
    SplayTree* massive = new SplayTree;
    unsigned int startTime = clock();
    if (algorithmChecker(massive, in)){
        std::cout << "OK" << std::endl;
    }
    else{
        std::cout << "Something went wrong" << std::endl;
    }
    unsigned int endTime = clock();
    in.close();
    delete massive;
    std::cout << "Program has worked for " << difftime (endTime, startTime) << std::endl;
    return 0;
}/**/