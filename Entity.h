#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
namespace pg
{

enum State {
    NIL,MAYBE,NO,YES,
};


struct EntityBase{


};


template<class INPUT,class OUTPUT>
struct Entity : std::enable_shared_from_this<Entity<INPUT, OUTPUT>>, public EntityBase {
    using Entityptr = std::shared_ptr<Entity<INPUT, OUTPUT>> ;
    using EntityMap = std::unordered_map<Entityptr,  OUTPUT>;
    using EntityBoolMap = std::unordered_map<Entityptr, bool>;
    using EntitySet = std::unordered_set<Entityptr>;

    INPUT inputType(){};
    OUTPUT outputType(){};



    virtual void add(const Entityptr ptr)
    {
        entities[ptr];
    }
    virtual void remove(const Entityptr ptr)
    {
        entities.erase(ptr);
    };

    void sendValue(const Entityptr ptr,OUTPUT dat);
    INPUT getValue(const Entityptr pt ) ;

    const EntitySet& getChangedEntities() const
    {
        return changedEntities;
    };
    const EntityMap& getEntities() const;

    void omniUpdate();
    void eurusUpdate();
    std::function<void(Entityptr)> updateFunc;
    std::function<void(Entityptr, INPUT)> memoryFunc;
public:
    void receiveData(Entityptr ptr, INPUT dat);
    bool omniChanged=0;///Changed to true when received Info
    EntityBoolMap eurusChangedMap;

    EntitySet changedEntities;
    EntityMap entities;

};

#define Entityptr std::shared_ptr<Entity<INPUT, OUTPUT>>
#define EntityMap std::unordered_map<Entityptr,  OUTPUT>
#define EntitySet std::unordered_set<Entityptr>


template <class INPUT,class OUTPUT>
INPUT Entity<INPUT, OUTPUT>::getValue(const Entityptr pt )
{
    return entities[pt];
}

template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::omniUpdate()
{
    for(auto& it:eurusChangedMap) {
        Entityptr ent = it.first;
        ent->receiveData(this->shared_from_this(), entities[ent]);
        changedEntities.erase(ent);
    }
    eurusChangedMap.clear();


}

template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::eurusUpdate()
{
    if(omniChanged && updateFunc) {
        updateFunc(this->shared_from_this());
        omniChanged = false;
    }
}


template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::receiveData(Entityptr ptr, INPUT dat)
{
    if(memoryFunc) {
        memoryFunc(ptr,dat);
    }
    changedEntities.insert(ptr);
    omniChanged = true;
}


template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::sendValue(const Entityptr ptr,OUTPUT dat)
{
    if(changedEntities.count(ptr)==0) {
        //    std::cerr<<"Sending data to unmodified entity"<<std::endl;
    }
    eurusChangedMap[ptr]=1;
    entities[ptr]=dat;
}

template <class INPUT,class OUTPUT>
const EntityMap& Entity<INPUT, OUTPUT>::getEntities() const
{
    return entities;
}

}

#undef Entityptr
#undef EntityMap
#undef EntitySet


