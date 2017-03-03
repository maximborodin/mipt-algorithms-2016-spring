#include <iostream>
#include "GarbageCollector.h"
#include "ObjectInterface.h"
#include <vector>


int main()
{
    std::vector<Object*> objects;
    for (int i = 0;i < 5;i++){
        objects.push_back(new Object());
        objects[i]->addPointer (objects[i]);
    }
    for (int i = 0;i < 55;i++){
        objects.push_back(new Object());
    }
    for (int i = 0;i < 54;i++){
        objects[i + 5]->addPointer(objects[i + 1]);
        objects[59]->addPointer(objects[5]);
    }
    for (int i = 0;i < 555;i++){
        new Object;
    }
    Object obj;
    obj.addPointer (new Object);
    obj.addPointer (new Object);
    GarbageCollector::Instance().RemoveInstance();
    return 0;
}