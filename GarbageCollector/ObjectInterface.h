//
// Created by Maxim on 5/22/2016.
//

#pragma once

#include <vector>
#include <cstdio>

class SmartObject
{
public:
    SmartObject();

    virtual std::vector<SmartObject* > pointers() const = 0; // возвращает указатели на объекты
    /*void* operator new (size_t size);*/

    virtual ~SmartObject();
};
