#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "Specials.h"
namespace pg
{

template<typename T>
struct enable_shared_from_this_virtual;

class enable_shared_from_this_virtual_base : public std::enable_shared_from_this<enable_shared_from_this_virtual_base>
{
    typedef std::enable_shared_from_this<enable_shared_from_this_virtual_base> base_type;
    template<typename T>
    friend struct enable_shared_from_this_virtual;

    std::shared_ptr<enable_shared_from_this_virtual_base> shared_from_this()
    {
        return base_type::shared_from_this();
    }
    std::shared_ptr<enable_shared_from_this_virtual_base const> shared_from_this() const
    {
       return base_type::shared_from_this();
    }
};

template<typename T>
struct enable_shared_from_this_virtual: virtual enable_shared_from_this_virtual_base
{
    typedef enable_shared_from_this_virtual_base base_type;

public:
    std::shared_ptr<T> shared_from_this()
    {
       std::shared_ptr<T> result(base_type::shared_from_this(), static_cast<T*>(this));
       return result;
    }

    std::shared_ptr<T const> shared_from_this() const
    {
        std::shared_ptr<T const> result(base_type::shared_from_this(), static_cast<T const*>(this));
        return result;
    }
};






struct OmniBase {
    virtual void omniUpdate()=0;
};
using Omniptr = std::shared_ptr<OmniBase>;

struct EurusBase {
    virtual void eurusUpdate()=0;
};
using Eurusptr = std::shared_ptr<EurusBase>;

template <class OUTPUT>
class Sender;

template <class OUTPUT>
class Sender;

template <class INPUT>
struct Receiver:public EurusBase {
    INPUT inputType() {};
    using Inputptr = std::shared_ptr<Sender<INPUT>> ;
};

template <class OUTPUT>
struct Sender:public OmniBase {
    OUTPUT outputType() {};
};



struct GlobalRunner: Singleton<GlobalRunner> {
    //TODO create per request entity runner
    template<class T>
    void addOmni(T ent)
    {
        omni.insert( ent->getOmniPtr() );
    }

    template<class T>
    void addEurus(T ent)
    {
        eurus.insert( ent->getEurusPtr() );
    }

    void update()
    {
        while(omni.size() || eurus.size()) {
            auto omniCopy = omni;
            auto eurusCopy = eurus;

            std::cerr<<"Updating:"<<omni.size()<<" "<<eurus.size()<<std::endl;
            omni.clear();
            eurus.clear();

            for(auto& x:omniCopy) {

                x->omniUpdate();
            }
            for(auto& x: eurusCopy) {
                x->eurusUpdate();
            }

        }

    }
    std::set<Omniptr> omni;
    std::set<Eurusptr> eurus;
};



template<class INPUT,class OUTPUT>
struct Entity : enable_shared_from_this_virtual<Entity<INPUT, OUTPUT>>, public Receiver<INPUT>, public Sender<OUTPUT>  {
    using Entityptr = std::shared_ptr<Entity<INPUT, OUTPUT>> ;
    using Negaptr = std::shared_ptr<Entity<OUTPUT, INPUT>> ;

    using Inputptr = std::shared_ptr<Sender<INPUT>> ;
    using Outputptr = std::shared_ptr<Receiver< OUTPUT>> ;

    using EntityMap = std::unordered_map<Negaptr,  OUTPUT>;
    using EntityBoolMap = std::unordered_map<Negaptr, bool>;
    using EntitySet = std::unordered_set< Negaptr >;

    void omniUpdate();
    void eurusUpdate();

    void sendValue(const Negaptr,OUTPUT dat);
    void receiveData(Negaptr ptr, INPUT dat);
    // void receiveData(Inputptr ptr, INPUT dat);

    INPUT inputType() {};
    OUTPUT outputType() {};

    Omniptr getOmniPtr()
    {
        auto me =this->shared_from_this();
        auto ret = std::static_pointer_cast<OmniBase>(me);
        return ret;
    }
    Eurusptr getEurusPtr()
    {
        auto me =this->shared_from_this();
        auto ret = std::static_pointer_cast<EurusBase>(me);
        return ret;
    }

    std::shared_ptr<Receiver<INPUT>> getInput()
    {
        auto me =this->shared_from_this();
        auto ret = std::static_pointer_cast<Receiver<INPUT>>(me);
        return ret;
    }
    std::shared_ptr<Sender<OUTPUT>> getOutput()
    {
        auto me =this->shared_from_this();
        auto ret = std::static_pointer_cast<Sender<OUTPUT>>(me);
        return ret;
    }


    virtual void add(const Negaptr ptr)
    {
        entities[ptr];
    }
    virtual void remove(const Negaptr ptr)
    {
        entities.erase(ptr);
    };


    OUTPUT getValue(const Negaptr pt );

    const EntitySet& getChangedEntities() const
    {
        return changedEntities;
    };
    const Negaptr getChanged() const
    {
        return *changedEntities.begin();
    };

    const EntityMap& getEntities() const;

protected:

    void setRunFunction(std::function<void(Entityptr)> func)
    {
        updateFunc = func;
    }
    void setMemoryFunction(std::function<void(Entityptr)> func)
    {
        updateFunc = func;
    }
    std::function<void(Entityptr)> updateFunc;
//   std::function<void(Entityptr, INPUT)> memoryFunc;
    std::function<void(Inputptr, INPUT)> memoryFunc;
public:
    bool omniChanged=0;///Changed to true when received Info
    EntityBoolMap eurusChangedMap;

    EntitySet changedEntities;
    EntityMap entities;
};

#define Entityptr std::shared_ptr<Entity<INPUT, OUTPUT>>
#define Negaptr std::shared_ptr<Entity<OUTPUT, INPUT>>

#define Inputptr std::shared_ptr<Sender<INPUT>>
#define Outputptr std::shared_ptr<Receiver< OUTPUT>>


#define EntityMap std::unordered_map<Negaptr,  OUTPUT>
#define EntitySet std::unordered_set<Inputptr>


template <class INPUT,class OUTPUT>
OUTPUT Entity<INPUT, OUTPUT>::getValue(const Negaptr pt )
{
    return entities[pt];
}

template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::omniUpdate()
{
    for(auto& it:eurusChangedMap) {
        Negaptr ent = it.first;
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
    }
    omniChanged = false;
}


template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::receiveData(Negaptr ptr, INPUT dat)
{
    if(memoryFunc) {
        memoryFunc(ptr,dat);
    }
    changedEntities.insert(ptr);
    omniChanged=true;
    GlobalRunner::get()->addEurus( this->shared_from_this());
}


template <class INPUT,class OUTPUT>
void Entity<INPUT, OUTPUT>::sendValue(const Negaptr ptr,OUTPUT dat)
{
    //TODO have not lose multiple send messages to same destination
    // if(changedEntities.count(ptr)==0) {
    //    std::cerr<<"Sending data to unmodified entity"<<std::endl;
    // }
    eurusChangedMap[ptr]=1;
    entities[ptr]=dat;
    GlobalRunner::get()->addOmni( this->shared_from_this());
}

template <class INPUT,class OUTPUT>
const EntityMap& Entity<INPUT, OUTPUT>::getEntities() const
{
    return entities;
}

}

#undef Entityptr
#undef Negaptr
#undef Inputptr
#undef Outputptr

#undef EntityMap
#undef EntitySet


