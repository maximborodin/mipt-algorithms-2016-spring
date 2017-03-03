//
// Created by maxim on 2/27/16.
//

#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>
#include "permutationInterface.h"


class STLRealize : public MassiveI
{
public:
    void add (int l, int r, int val)
    {
        if (l > r){
            std::swap(l, r);
        }
        std::for_each (arr.begin() + l, arr.begin() + r + 1, [val](int &n){n += val;});
    }
    void replace (int ind, int val)
    {
        arr[ind] = val;
    }
    void insert (int ind, int val)
    {
        std::vector<int>::iterator it = arr.begin();
        it += ind;
        arr.insert(it, val);
    }
    void nextPermutation (int l, int r)
    {
        if (l > r){
            std::swap(l, r);
        }
        std::next_permutation(arr.begin() + l, arr.begin() + r + 1);
    }
    int sum (int l, int r)
    {
        if (l > r){
            std::swap(l, r);
        }
        int result = std::accumulate (arr.begin() + l, arr.begin() + r + 1, 0);
        return result;
    }
    std::vector<int> getMassive()
    {
        return arr;
    }
/*private:
    std::vector<int> arr;*/
};
