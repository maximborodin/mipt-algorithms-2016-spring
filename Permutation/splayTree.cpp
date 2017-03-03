#include "splayTree.h"
#include <iostream>

void SplayTree::insert(int ind, int val)
{
    Node* node = new Node(val);
    Node* rightTree = split(ind - 1);
    merge(node);
    merge(rightTree);
}

void SplayTree::replace(int ind, int val)
{
    Node* rightTree = split(ind);
    head->val = val;
    update(head);
    merge(rightTree);
}

void SplayTree::add(int l, int r, int val) 
{
    Node* rightTree = split(r);
    Node* leftTree = split(l - 1);
    leftTree->pushAdd += val;
    merge(leftTree);
    merge(rightTree);
}

void SplayTree::nextPermutation(int l, int r)
{
    Node* rightTree = split(r);
    push(head);
    if ((r - l + 1) <= getMaxSuf(head)) {
        Node* leftTree = split(l - 1);
        leftTree->isReversed = !leftTree->isReversed;
        merge(leftTree);
    }
    else {
        int ind = r - getMaxSuf(head);
        Node* leftTree = split(ind);
        push(leftTree);
        int val = head->val;
        bool ok = true;
        while (ok) {
            if (leftTree->val > val && leftTree->right != nullptr) {
                leftTree = leftTree->right;
                push(leftTree);
            }
            else if (leftTree->val <= val && leftTree->left != nullptr) {
                leftTree = leftTree->left;
                push(leftTree);
            }
            else {
                ok = false;
            }
        }
        while (leftTree->val <= val) {
            leftTree = leftTree->parent;
        }
        std::swap(head->val, leftTree->val);
        update(head);
        update(leftTree);
        while (leftTree->parent != nullptr) {
            splay(leftTree);
        }
        leftTree->isReversed = !leftTree->isReversed;
        merge(leftTree);
    }
    merge(rightTree);
}

int SplayTree::sum(int l, int r)
{
    Node* rightTree = split(r);
    Node* leftTree = split(l - 1);
    int ans = getSum(leftTree);
    merge(leftTree);
    merge(rightTree);
    return ans;
}

std::vector<int> SplayTree::getMassive()
{
    arr.clear();
    inOrder(head);
    return arr;
}

void SplayTree::inOrder (Node* node)
{
    if (node == nullptr){
        return;
    }
    push(node);
    inOrder(node->left);
    arr.push_back(node->val);
    inOrder(node->right);
}


int SplayTree::getSum(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    return (node->pushAdd * node->subTreeCount) + node->subTreeSum ;
}

int SplayTree::getLastVal(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    if (node->isReversed){
        return (node->firstVal + node->pushAdd);
    }
    return (node->lastVal + node->pushAdd);
}

int SplayTree::getFirstVal(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    if (node->isReversed){
        return (node->lastVal + node->pushAdd);
    }
    return (node->firstVal + node->pushAdd);
}

int SplayTree::getCount(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    return node->subTreeCount;
}

int SplayTree::getMaxSuf(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    if (node->isReversed){
        return (node->maxPref);
    }
    return node->maxSuf;
}

int SplayTree::getMaxPref(Node* node)
{
    if (node == nullptr) {
        return 0;
    }
    if (node->isReversed){
        return (node->maxSuf);
    }
    return node->maxPref;
}

void SplayTree::leftSpin(Node* node)
{
    Node* parent = node->parent;
    push(parent);
    push(node);
    parent->right = node->left;
    node->left = parent;

    if (parent->right != nullptr) {
        parent->right->parent = parent;
    }
    node->parent = parent->parent;
    parent->parent = node;
    if (node->parent != nullptr) {
        if (node->parent->left == parent) {
            node->parent->left = node;
        }
        else {
            node->parent->right = node;
        }
    }
    update(parent);
    update(node);
}

void SplayTree::rightSpin(Node* node)
{
    Node* parent = node->parent;
    push(parent);
    push(node);
    parent->left = node->right;
    node->right = parent;

    if (parent->left != nullptr) {
        parent->left->parent = parent;
    }
    node->parent = parent->parent;
    parent->parent = node;
    if (node->parent != nullptr) {
        if (node->parent->left == parent) {
            node->parent->left = node;
        }
        else {
            node->parent->right = node;
        }
    }
    update(parent);
    update(node);
}

void SplayTree::zig(Node* node)
{
    Node* parent = node->parent;
    if (parent->left == node) {
        rightSpin(node);
    }
    else {
        leftSpin(node);
    }
}

void SplayTree::zigZig(Node* node)
{
    Node* parent = node->parent;
    Node* grandParent = parent->parent;

    if (parent == grandParent->left && node == parent->left) {
        rightSpin(parent);
        rightSpin(node);
    }
    else {
        leftSpin(parent);
        leftSpin(node);
    }
}

void SplayTree::zigZag(Node* node)
{
    Node* parent = node->parent;
    Node* grandParent = parent->parent;

    if (parent == grandParent->left && node == parent->right) {
        leftSpin(node);
        rightSpin(node);
    }
    else {
        rightSpin(node);
        leftSpin(node);
    }
}

void SplayTree::update(Node* node)
{
    if (node == nullptr) {
        return;
    }
    node->subTreeCount = getCount(node->left) + getCount(node->right) + 1;
    node->subTreeSum = getSum(node->left) + getSum(node->right) + node->val;
    node->maxSuf = getMaxSuf(node->right);

    if (getMaxSuf(node->right) == getCount(node->right)) {
        if (node->right == nullptr || node->val >= getFirstVal(node->right)) {
            node->maxSuf++;
            if (node->left != nullptr && getLastVal(node->left) >= node->val) {
                node->maxSuf += getMaxSuf(node->left);
            }
        }
    }
    node->maxPref = getMaxPref(node->left);
    if (getMaxPref(node->left) == getCount(node->left)) {
        if (node->left == nullptr || node->val >= getLastVal(node->left)) {
            node->maxPref++;
            if (node->right != nullptr && getFirstVal(node->right) >= node->val) {
                node->maxPref += getMaxPref(node->right);
            }
        }
    }
    if (node->right != nullptr) {
        node->lastVal = getLastVal(node->right);
    }
    else {
        node->lastVal = node->val;
    }
    if (node->left != nullptr) {
        node->firstVal = getFirstVal(node->left);
    }
    else {
        node->firstVal = node->val;
    }
}

void SplayTree::push(Node* node)
{
    if (node == nullptr) {
        return;
    }
    if (node->pushAdd != 0) {
        node->val += node->pushAdd;
        node->subTreeSum += node->pushAdd * getCount(node);
        node->lastVal += node->pushAdd;
        node->firstVal += node->pushAdd;

        if (node->left != nullptr) {
            node->left->pushAdd += node->pushAdd;
        }
        if (node->right != nullptr) {
            node->right->pushAdd += node->pushAdd;
        }
        node->pushAdd = 0;
    }
    if (node->isReversed) {
        std::swap(node->left, node->right);
        if (node->left != nullptr) {
            node->left->isReversed = !node->left->isReversed;
        }
        if (node->right != nullptr) {
            node->right->isReversed = !node->right->isReversed;
        }
        std::swap(node->firstVal, node->lastVal);
        std::swap(node->maxPref, node->maxSuf);
        node->isReversed = !node->isReversed;
    }
}

void SplayTree::splay(Node* node)
{
    Node* parent = node->parent;
    if (parent == nullptr) return;

    Node* grandParent = parent->parent;

    if (grandParent == nullptr) {
        zig(node);
    }
    else {
        if ((parent == grandParent->left && node == parent->left) ||
            (parent == grandParent->right && node == parent->right)) {
            zigZig(node);
        }
        else {
            zigZag(node);
        }
    }
}

SplayTree::Node*  SplayTree::split(int ind)
{
    if (head == nullptr) {
        return nullptr;
    }
    Node* node = head;
    push(node);
    int nodePosition = getCount(node->left);

    while (nodePosition != ind) {
        if (nodePosition < ind && node->right != nullptr) {
            node = node->right;
            push(node);
            nodePosition += getCount(node->left) + 1;
        }
        else if (nodePosition > ind && node->left != nullptr) {
            node = node->left;
            push(node);
            nodePosition -= getCount(node->right) + 1;
        }
        else {
            break;
        }
    }
    while (node->parent != nullptr) {
        splay(node);
    }
    if (ind < 0) {
        head = nullptr;
        return node;
    }
    else {
        if (node->right != nullptr) {
            node->right->parent = nullptr;
        }
        Node* otherNode = node->right;
        node->right = nullptr;
        update(node);
        head = node;
        return otherNode;
    }
}

void SplayTree::merge(Node* secondNode)
{
    Node* node = head;
    push(node);
    if (node == nullptr) {
        head = secondNode;
    }
    else {
        while (node->right != nullptr) {
            node = node->right;
            push(node);
        }
        while (node->parent != nullptr) {
            splay(node);
        }
        if (secondNode != nullptr) {
            secondNode->parent = node;
        }
        node->right = secondNode;
        update(node);
        head = node;
    }
}