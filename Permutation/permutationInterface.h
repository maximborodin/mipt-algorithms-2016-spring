//
// Created by maxim on 2/25/16.
//
#pragma once

class MassiveI
{
public:
    /*virtual ~MassiveI(){}*/
    virtual void add (int l, int r, int val) = 0;
    virtual void replace (int ind, int val) = 0;
    virtual void insert (int ind, int val) = 0;
    virtual void nextPermutation (int l, int r) = 0;

    virtual int sum (int l, int r) = 0;

    virtual std::vector<int> getMassive() = 0;

protected:
    std::vector<int> arr;
};

