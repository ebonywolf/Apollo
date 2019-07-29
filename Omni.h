#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "Memory.h"
namespace pg
{

/*
template <class Data>
struct Entity : std::enable_shared_from_this< Entity<Data> >;


template<class Data>
struct Eurus : std::enable_shared_from_this< Eurus<Data> > {

};
*/
enum State {
    NIL,MAYBE,NO,YES,
};


template<class Data>
struct Entity : std::enable_shared_from_this<Entity<Data>> {
    using Entityptr = std::shared_ptr<Entity<Data>> ;
    using EntityMap = std::unordered_map<Entityptr, Data>;
    using EntityBoolMap = std::unordered_map<Entityptr, bool>;


    using EntitySet = std::unordered_set<Entityptr>;
    using Memoryptr = std::shared_ptr<Memory<Data>>;


    void add(Entityptr ptr) ;
    void remove(Entityptr ptr) const;

    void sendData(Entityptr ptr, Data dat);
    void warnEurusChange(Entityptr ptr);
    Data getValue(Entityptr pt ) const;

    const EntitySet& getChangedEntities() const;
    const EntityMap& getEntities() const;

    void omniUpdate();
    std::function<void(Entityptr)> updateFunc;
    std::function<void(Entityptr, Data)> memoryFunc;
protected:

    bool omniChanged=0;///Changed to true when received Info
    EntityBoolMap eurusChangedMap;

    EntitySet changedEntities;
    EntityMap entities;

};

#define Entityptr std::shared_ptr<Entity<Data>>
#define EntityMap std::unordered_map<Entityptr, Data>
#define EntitySet std::unordered_set<Entityptr>


template <class Data>
void Entity<Data>::add(Entityptr ptr)
{
    entities[ptr];
}

template <class Data>
Data Entity<Data>::getValue(Entityptr pt ) const
{
    return entities[pt];
}

template <class Data>
void Entity<Data>::omniUpdate()
{
    if(omniChanged && updateFunc) {
        updateFunc(this->shared_from_this());
    }

    for(auto& it:eurusChangedMap)
    {
        Entityptr ent = it.first;
        ent->sendData(this->shared_from_this(), it.second);
        it.second = false;
    }
    /*
    if( eurusChanged ) {
        for(auto& it:entities) {

            entities[pt]=
            ent->sendData(this->shared_from_this(), it.second);
        }
    }
    */
  //  eurusChanged=false;
}


template <class Data>
void Entity<Data>::sendData(Entityptr ptr, Data dat)
{
    if(memoryFunc) {
        memoryFunc(ptr,dat);
    }
    changedEntities.insert(ptr);
    omniChanged = true;
}


template <class Data>
void Entity<Data>::setEurusChange(Entityptr ptr,Data dat)
{
    eurusChangedMap[ptr];
    entities[ptr]=dat;
    eurusChanged = true;
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


