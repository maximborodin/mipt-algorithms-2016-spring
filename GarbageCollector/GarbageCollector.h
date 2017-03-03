#pragma once
#include <vector>
#include <iostream>
#include "ObjectInterface.h"
#include <set>
#include <queue>

class Object : public SmartObject
{
public:
    std::vector<SmartObject*> pointers () const;
    void* operator new(size_t size);
    void addPointer(SmartObject*);

private:
    std::vector<SmartObject*> pointersArr;
};


class GarbageCollector
{
public:
    static GarbageCollector& Instance()  /*создание: GarbageCollector::Instance();*/
    {
        static GarbageCollector collector;
        return collector;
    }
    void RemoveInstance() //вместо деструктора
    {
        stackObjects.clear();
        collect();
    }
    void* heapAllocate(size_t size);
    void addObject(SmartObject* object);
    void removeObject(SmartObject* object);

    void collect();
    const unsigned int getMaxSize() const;
    unsigned int getUsedMemory () const;
private:
    GarbageCollector()
    {
        used.clear();
        heapObjects.clear();
        stackObjects.clear();
    } /* конструктор недоступен*/
    ~GarbageCollector() {} /* деструктор недоступен*/

    GarbageCollector (GarbageCollector const&) = delete; /*Запрещаем констуктор копирования*/
    GarbageCollector& operator= (GarbageCollector const&) = delete;

    void bfs(SmartObject* object);

    std::set<SmartObject*> stackObjects;
    std::set<SmartObject*> heapObjects;

    std::set<SmartObject*> used;

    unsigned int usedMemory = 0;
    const unsigned int MAX_SIZE = 10000;
};