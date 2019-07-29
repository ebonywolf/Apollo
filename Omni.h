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
    using EntitySet = std::unordered_set<Entityptr>;
    using Memoryptr = std::shared_ptr<Memory<Data>>;


    void add(Entityptr ptr) ;
    void remove(Entityptr ptr) const;

    bool warnOmniChange(Entityptr ptr, Data dat);
    bool warnEurusChange(Entityptr ptr);
    Data getValue(Entityptr pt ) const;

    const EntitySet& getChangedEntities() const;
    const EntityMap& getEntities() const;

    void omniUpdate();
    std::function<void(Entityptr)> updateFunc;
    std::function<void(Entityptr, Data)> memoryFunc;
protected:

    bool omniChanged=0;///Changed to true when received Info
    bool eurusChanged=0;///Changed to true when sending Info

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
    entities[pt];
}

template <class Data>
void Entity<Data>::omniUpdate()
{
    if(omniChanged && updateFunc) {
        updateFunc(this->shared_from_this());
    }

    if( eurusChanged ) {
        for(auto& it:entities) {
            Entityptr ent = it.first;

            ent->warnOmniChange(this->shared_from_this(), it.second);
        }
    } else {

    }
    eurusChanged=false;
}


template <class Data>
bool Entity<Data>::warnOmniChange(Entityptr ptr, Data dat)
{
    if(memoryFunc) {

        memoryFunc(ptr,dat);
    }
    changedEntities.insert(ptr);
    omniChanged = true;
}


template <class Data>
bool Entity<Data>::warnEurusChange(Entityptr ptr)
{

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


