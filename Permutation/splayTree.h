#pragma once

#include <algorithm>
#include "permutationInterface.h"

class SplayTree : public MassiveI
{
public:
    SplayTree()
    {
        head = nullptr;
    }
    SplayTree(int val)
    {
        head = new Node(val);
    }
    ~SplayTree()
    {
        delete head;
    }
    
    
    void insert(int ind, int val);
    void replace(int ind, int val);
    void add(int l, int r, int val);
    void nextPermutation(int l, int r);

    int sum(int l, int r);

    std::vector<int> getMassive();

private:
    class Node
    {
    public:
        Node(int val_) : val(val_), subTreeSum(val_), lastVal(val_), firstVal(val_),
                         parent(nullptr), left(nullptr), right(nullptr),
                         maxSuf(1), maxPref(1), pushAdd(0), isReversed(false) {}

        ~Node()
        {
            delete left;
            delete right;
        }

        Node* left;
        Node* right;
        Node* parent;
        int val, subTreeCount, subTreeSum, pushAdd;
        int firstVal, lastVal, maxPref, maxSuf;
        bool isReversed;
    };

    SplayTree(Node* node) : head(node) { }

    void inOrder (Node* node);

    int getSum(Node* node);
    int getLastVal(Node* node);
    int getFirstVal(Node* node);
    int getCount(Node* node);
    int getMaxSuf(Node* node);
    int getMaxPref(Node* node);

    void leftSpin(Node* node);
    void rightSpin(Node* node);
    void splay(Node* node);

    void zig(Node* node);
    void zigZig(Node* node);
    void zigZag(Node* node);

    void update(Node* node);
    void push(Node* node);

    void merge(Node* otherNode);
    Node* split(int ind);

    Node* head;
};