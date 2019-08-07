#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "Memory.h"
namespace pg
{


enum State {
    NIL,MAYBE,NO,YES,
};


template<class Data>
struct Entity : std::enable_shared_from_this<Entity<Data>> {
    using Entityptr = std::shared_ptr<Entity<Data>> ;
    using EntityMap = std::unordered_map<Entityptr, Data>;
    using EntityBoolMap = std::unordered_map<Entityptr, bool>;
    using EntitySet = std::unordered_set<Entityptr>;


    void add(const Entityptr ptr) {entities[ptr];}
    void remove(const Entityptr ptr) {entities.erase(ptr);};

    void sendData(const Entityptr ptr,Data dat);
    Data getValue(const Entityptr pt ) ;

    const EntitySet& getChangedEntities() const{
        return changedEntities;
    };
    const EntityMap& getEntities() const;

    void omniUpdate();
    std::function<void(Entityptr)> updateFunc;
    std::function<void(Entityptr, Data)> memoryFunc;
protected:
    void receiveData(Entityptr ptr, Data dat);
    bool omniChanged=0;///Changed to true when received Info
    EntityBoolMap eurusChangedMap;

    EntitySet changedEntities;
    EntityMap entities;

};

#define Entityptr std::shared_ptr<Entity<Data>>
#define EntityMap std::unordered_map<Entityptr, Data>
#define EntitySet std::unordered_set<Entityptr>


template <class Data>
Data Entity<Data>::getValue(const Entityptr pt )
{
    return entities[pt];
}

template <class Data>
void Entity<Data>::omniUpdate()
{
    for(auto& it:eurusChangedMap)
    {
        Entityptr ent = it.first;
        ent->receiveData(this->shared_from_this(), entities[ent]);
        changedEntities.erase(ent);
    }
    eurusChangedMap.clear();

    if(omniChanged && updateFunc) {
        updateFunc(this->shared_from_this());
        omniChanged = false;
    }
}


template <class Data>
void Entity<Data>::receiveData(Entityptr ptr, Data dat)
{
    if(memoryFunc) {
        memoryFunc(ptr,dat);
    }
    changedEntities.insert(ptr);
    omniChanged = true;
}


template <class Data>
void Entity<Data>::sendData(const Entityptr ptr,Data dat)
{
    eurusChangedMap[ptr]=1;
    entities[ptr]=dat;
}

template <class Data>
const EntityMap& Entity<Data>::getEntities() const
{
    return entities;
}

}

#undef Entityptr
#undef EntityMap
#undef EntitySet


