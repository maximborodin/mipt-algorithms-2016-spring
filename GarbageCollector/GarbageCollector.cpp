//
// Created by Maxim on 5/22/2016.
//
#include "GarbageCollector.h"
#include <stdexcept>


SmartObject::SmartObject()
{
    GarbageCollector::Instance().addObject(this);
}

SmartObject::~SmartObject()
{
    GarbageCollector::Instance().removeObject(this);
}

std::vector<SmartObject*> Object::pointers() const
{
    return pointersArr;
}

void* Object::operator new (size_t size)
{
    return (GarbageCollector::Instance().heapAllocate(size));
}

void Object::addPointer (SmartObject* other)
{
    pointersArr.push_back(other);
}

//--------------------Collector--------------------------------

void* GarbageCollector::heapAllocate(size_t size)
{
    if (getUsedMemory() + size > getMaxSize()){
        collect();
    }
    if (getUsedMemory() + size > getMaxSize()){
        throw std::bad_alloc();
    }
    SmartObject* res = static_cast<SmartObject*>(malloc(size));
    if (res == nullptr){
        throw std::bad_alloc();
    }
    usedMemory += size;
    heapObjects.insert(res);
    return res;
}

void GarbageCollector::addObject (SmartObject* object)
{
    if (heapObjects.count(object) == 0){
        stackObjects.insert(object);
    }
}

void GarbageCollector::removeObject (SmartObject* object)
{
    if (heapObjects.count(object) == 0)
    {
        if (stackObjects.count(object) == 0)
        {
            return;
        }
        stackObjects.erase(stackObjects.find(object));
        return;
    }
    heapObjects.erase(heapObjects.find(object));
    usedMemory -= sizeof(*object);
}


void GarbageCollector::collect()
{
    for (const auto& i : stackObjects){
        if (used.count(i) != 0){
            bfs(i);
        }
    }
    std::vector<SmartObject*> forRemoving;
    /*std::set<SmartObject*>::iterator it;
    for (it = heapObjects.begin(); it != heapObjects.end();it++){
        if (used.count(*it) == 0){
            forRemoving.push_back(*it);
        }
    }*/
    for (const auto& it : heapObjects){
        if (used.count(it) == 0){
            forRemoving.push_back(it);
        }
    }
    for (size_t i = 0;i < forRemoving.size();i++){
        heapObjects.erase(forRemoving[i]);
        delete(forRemoving[i]);
    }
    used.clear();
}

unsigned int GarbageCollector::getUsedMemory() const
{
    return usedMemory;
}

const unsigned int GarbageCollector::getMaxSize() const
{
    return MAX_SIZE;
}

void GarbageCollector::bfs (SmartObject* object)
{
    std::queue<SmartObject*> queue;
    queue.push(object);
    used.insert(object);
    while (!queue.empty()){
        SmartObject* v = queue.front();
        queue.pop();
        std::vector<SmartObject*> pointers = v->pointers();
        for (size_t i = 0; i < pointers.size(); ++i) {
            SmartObject* to = pointers[i];
            if (used.count(to) == 0) {
                used.insert(to);
                queue.push (to);
            }
        }
    }
}