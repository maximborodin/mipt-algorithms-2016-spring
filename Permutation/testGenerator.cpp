//
// Created by maxim on 2/27/16.
//
/*

#include <iostream>
#include <fstream>
#include <ctime>



const int MAX_SIZE = 10000;

enum types {Add, Replace, Sum, Insert, NextPermutation};

void mixTest (std::ofstream& out)
{
    int queries = rand () % (MAX_SIZE - 5);
    queries += 5;
    //queries = 10;
    out << queries << "\n";
    int curSize = 0;
    for (int i = 0;i < 5;i++){
        int val = i;
        out << "insert " << i << " " << val << "\n";
        curSize++;
    }
    for (int i = 0;i < queries - 5;i++){
        int type = rand () % 5;
        int l, r, val, ind;
        switch (type){
            case Add:
                l = rand () % curSize;
                r = rand () % curSize;
                val = rand () % MAX_SIZE;
                if (l > r){
                    std::swap(l, r);
                }
                out << "add " << l << " " << r << " " << val << "\n";
                break;
            case Replace:
                ind = rand () % curSize;
                val = rand() % MAX_SIZE;
                out << "replace " << ind << " " << val << "\n";
                break;
            case Sum:
                l = rand () % curSize;
                r = rand () % curSize;
                if (l > r){
                    std::swap(l, r);
                }
                out << "sum " << l << " " << r << "\n";
                break;
            case Insert:
                ind = rand () % curSize;
                val = rand () % MAX_SIZE;
                out << "insert " << ind << " " << val << "\n";
                curSize++;
                break;
            case NextPermutation:
                l = rand () % curSize;
                r = rand () % curSize;
                if (l > r){
                    std::swap(l, r);
                }
                out << "nextPermutation " << l << " " << r << "\n";
                break;
        }
    }
}

void permutationTest (std::ofstream& out)
{
    int queries = rand () % (MAX_SIZE - 5);
    queries += 5;
    int curSize = 0;
    for (int i = 0;i < (queries + 1) / 2;i++){
        int val = rand () % MAX_SIZE;
        out << i << " " << val << "\n";
        curSize++;
    }
    for (int i = 0;i < (queries / 2);i++) {
        int l, r;
        l = rand() % curSize;
        r = rand() % curSize;
        if (l > r){
            std::swap(l, r);
        }
        out << "nextPermutation " << l << " " << r << "\n";
    }
}

void arrTest (std::ofstream& out)
{
    int queries = rand () % (MAX_SIZE - 5);
    queries += 5;
    int curSize = 0;
    for (int i = 0;i < 5;i++){
        int val = rand () % MAX_SIZE;
        out << i << " " << val << "\n";
        curSize++;
    }
    for (int i = 0;i < queries - 5;i++){
        int type = rand () % 4;
        int l, r, val, ind;
        switch (type){
            case Add:
                l = rand () % curSize;
                r = rand () % curSize;
                if (l > r){
                    std::swap(l, r);
                }
                val = rand () % MAX_SIZE;
                out << "add " << l << " " << r << " " << val << "\n";
                break;
            case Replace:
                ind = rand () % curSize;
                val = rand() % MAX_SIZE;
                out << "replace " << ind << " " << val << "\n";
                break;
            case Sum:
                l = rand () % curSize;
                r = rand () % curSize;
                if (l > r){
                    std::swap(l, r);
                }
                out << "sum " << l << " " << r << "\n";
                break;
            case Insert:
                ind = rand () % curSize;
                val = rand () % MAX_SIZE;
                out << "insert " << ind << " " << val << "\n";
                curSize++;
                break;
        }
    }
}


int main ()
{
    srand(time(NULL));
    std::ofstream out;
    out.open ("test.txt", std::ofstream::out);
    mixTest (out);
    //permutationTest (out);
    //arrTest (out);
    out.close();
}
/**/