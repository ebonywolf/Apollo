#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <fstream>
#include <future>
#include <iostream>
#include <json/json.h>
#include "Data.h"
#include "Process.h"

namespace pg
{

struct EntityptrHash{
    std::size_t operator()(const pg::Entityptr& k) const;
};


struct EntitySet: std::unordered_set<Entityptr,EntityptrHash>
{

};

struct EntityMap : public std::unordered_map<DataPair,EntitySet> {
    using  std::unordered_map<DataPair,EntitySet>::unordered_map;

    EntitySet& operator()(const Datatype& from,const Datatype& to)
    {
        DataPair par (from,to);
        return operator [] (par);
    }
    const  EntitySet& operator()(const Datatype& from,const Datatype& to) const
    {
        DataPair par (from,to);
        if(!count(par))throw "foo";
        return at(par);
    }


};

struct Request {
    Request(Entityptr from,Entityptr to,const Data& sentData, Datatype request)
    {
    }

};

struct Entity_Base : public enable_shared_from_this_virtual<Entity> {
};


#define GLOBAL "_Global"

struct Entity : Entity_Base {//Defines object that runs many functions and has many dataTypes
    using ContextMap = std::unordered_map<std::string,Entityptr>;

    ContextMap _omni;
    EntityMap _eurus;
    ProcessList processes;

    Entity()
    {
        //     _omni[GLOBAL] = getGlobal();
    };

    template <class ...T>
    Entity(T...t)
    {
        addProcess(t...);
    };

    template <class INPUT, class OUTPUT>
    void addProcess( OUTPUT(func)(INPUT) )
    {
        Processptr p = Processptr (new GenericProcess<INPUT,OUTPUT>(func));
        processes.insert(p);
    }


    template <class INPUT, class OUTPUT,class ...T>
    void addProcess(OUTPUT(func)(INPUT), T ...t)
    {
        addProcess(func);
        addProcess(t...);
    }

    ProcessList getProcess()
    {
        return processes;
    }
    bool hasMethod(Datatype from, Datatype to) const
    {
        DataPair par (from,to);
        return hasMethod(par);
    }
    bool hasMethod( DataPair par ) const
    {
        return processes.count(par) || _eurus.count(par);
    }
    bool hasOmni(std::string name) const
    {
        return _omni.count(name);
    }

    void addOmni(std::string name,const Entityptr obj)
    {
        _omni[name]=obj;
    }

    void addEurus( const Entityptr obj)
    {
        for(auto& proc: obj->getProcess()) {
            const Datatype from  = proc->getFrom();
            const Datatype to =  proc->getTo();
            auto& myset = _eurus(from,to);
            myset.insert(obj);
        }
    }
    void run()
    {

    }
    Data& send(const Data& sentData,const Datatype receiveType )const
    {

    }
    template<class T>
    Data& send(const Data& sentData )const
    {

        //const Data& sentData
        T received;
        const auto fromType = received.getType();
        const auto toType = sentData.getType();
        DataPair pair(fromType, toType);
        DataPair reversePair = pair.getInverse();

        bool sent=false;

        for (auto& it: _omni) {
            auto context = it.second;

            if(context->hasMethod(reversePair)) {
                sent=true;
            }

            context->omniUpdate( this->shared_from_this(),sentData,reversePair);
        }
        if(!sent) {
            throw std::runtime_error(std::string("no handler for: ")+reversePair.getHashKey());
        }
    }
    void omniUpdate( const C_Entityptr from,const Data& sentData, DataPair request)
    {

    }
    void extend(Entityptr other){
        addEurus(other);
        for(auto& x: other->_omni)
        {
            std::string name=x.first;
            auto otherOmni = x.second;
            addOmni(name,otherOmni);
        }
    }

    virtual std::string getName() const
    {
        throw "Its actually pure virtual";
    }

    Entityptr getOmni(std::string name) const
    {
        if(_omni.count(name)) {
            return _omni.at(name);
        } else {
            throw std::runtime_error(std::string("entity not present in context: ")+name);
        }
    }

    static Entityptr getGlobal()
    {
        static Entityptr global;
        if(!global) {
            global = Entityptr(new Entity());
            // global->["GLOBAL"] = global;//shared ptr pointing to itself,
        }
        return global;
    }

protected:
    struct PlaceHolder {
        PlaceHolder(){
        }
    };

    template<class T>
    static PlaceHolder createGlobalEntity(){
        Entityptr novo = Entityptr(new T());
        auto global = Entity::getGlobal();

        global->addOmni(novo->getName(), novo);
        global->addEurus( novo);
    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};

#define TO_STR(X) #X
template <class T>
class GenericEntity: public Entity
{
public:
    template <class ...D>
    GenericEntity(std::string name, D... t ) : Entity(t...), name(name)
    {
    };


    std::string getName() const
    {
        return name;
    }
    static PlaceHolder _instance;
    static_assert(&_instance);
    GenericEntity(PlaceHolder)
    {

    }
protected:
    std::string name;

} ;

template <class T>
Entity::PlaceHolder GenericEntity<T>::_instance = Entity::createGlobalEntity<T>();
//std::make_shared<GenericEntity<T>>(PlaceHolder());


class JsonEntity : public Entity
{
public:
    JsonEntity(std::string _name,Json::Value val):_name(_name)
    {
        for(auto& name: val.getMemberNames()) {
            Json::Value& subval = val[name];
            if(subval.isObject()) {

                Entityptr toadd = Entityptr(new JsonEntity(name, subval));
                addEurus(toadd);

                auto global = getGlobal();

                std::cerr<<"Global Size:"<<global->_eurus.size()<<std::endl;


                if( global->hasOmni(name) ) {
                    std::cerr<<"Adding"<<name<<std::endl;
                    auto current = global->getOmni(name);
                    current->extend(toadd);
                    global->addEurus(current);

                }else{
                    std::cerr<<"Creating"<<name<<std::endl;
                    global->addOmni(name,toadd);
                    global->addEurus(toadd);
                }

            } else {
                //  throw "foo";
            }

        }

    }
    virtual std::string getName()
    {
        return _name;
    }
    std::string _name;
};


struct ContextCreator {

    static Entityptr createFromJson(std::string file)
    {
        std::ifstream in(file);
        if(!in.is_open()) {
            throw "unable to open file";
        }
        Json::Value val;

        in>>val;
        Entityptr novo = Entityptr(new JsonEntity(file,val));

        return novo;
    }

};

}
