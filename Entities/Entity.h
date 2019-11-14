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
#include "Packet.h"

namespace pg
{

struct EntityptrHash{
    std::size_t operator()(const pg::Entityptr& k) const;
};


struct Entitycmp
{
  bool operator() (const Entityptr& t1, const Entityptr& t2) const;
};

struct EntitySet: public std::unordered_set<Entityptr,EntityptrHash,Entitycmp>
{
    bool contains(std::string name) const;
    Entityptr get(std::string name) const;

};

struct EntityMap : public std::unordered_map<DataPair,Entityptr> {
    using  std::unordered_map<DataPair,Entityptr>::unordered_map;

    Entityptr& operator()(const Datatype& from,const Datatype& to)
    {
        DataPair par (from,to);
        return operator [] (par);
    }
    const  Entityptr& operator()(const Datatype& from,const Datatype& to) const
    {
        DataPair par (from,to);
        if(!count(par))throw "foo";
        return at(par);
    }
};


struct Entity_Base : public enable_shared_from_this_virtual<Entity> {

};


#define GLOBAL "_Global"

struct Entity : Entity_Base  {//Defines object that runs many functions and has many dataTypes
    using ContextMap = std::unordered_map<std::string,Entityptr>;
    using SendBuffer = std::unordered_map<Entityptr, std::unordered_map<Entityptr,Packet>>;
    using PacketList = std::vector<Packet>;

    PacketMap _sentBuffer;
    PacketMap _receivedBuffer;
    EntitySet _senders;
    EntitySet _receivers;

   // SendBuffer _sentBuffer;
    EntitySet _omni;
    EntityMap _eurus;
    ProcessList processes;

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

    void handle(Packet p);

    ProcessList getProcess() const
    {
        ProcessList alce = processes;
        for(auto& it: _eurus)
        {
            Processptr novo = std::make_shared<Process>(it.first);
            alce.insert(novo);
        }
        return alce;
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
        return _omni.contains(name);
    }
    void addOmni(const Entityptr obj)
    {
        _omni.insert(obj);
    }

    void addEurus( const Entityptr obj);
    void omniUpdate(const Entityptr context)
    {
        auto packets = _sentBuffer.pull(context);
        for (auto& pack: packets) {
            auto thisPtr = this->shared_from_this();
            Packet request(thisPtr,pack.data, pack.futureAnswer, pack.context);
            pack.destination->receiveData(context, request);
        }
    }
    void eurusUpdate(const Entityptr context)
    {
        auto packets = _receivedBuffer.pull(context);
        for (auto& pack: packets) {
            auto handler =_eurus[pack.getChannel()];
            handler->handle(pack);
        }

    }
    Future send(Dataptr sentData, const Datatype fromType, Entityptr context );


    template<class T,class D>
    Future send( D d  )
    {

        Dataptr sentData = std::static_pointer_cast(d);
        Entityptr context= this->shared_from_this();
        T received;
        const auto fromType = received.getType();
        return send(sentData, fromType,context );
    }
    void receiveData(Entityptr context, Packet packet)
    {
        //TODO MEMORY FUNCTION
        _receivedBuffer.push(context, packet);
        context->warnEurusChange(this->shared_from_this());
    }

    void extend(Entityptr other){
        addEurus(other);
        for(auto ent: other->_omni)
        {
            addOmni(ent);
        }
    }

    virtual std::string getName() const=0;
    /*
    {
        throw "Its actually pure virtual method, it must be extended";
    }
    */

    Entityptr getOmni(std::string name) const
    {
        if(_omni.contains(name)) {
            return _omni.get(name);
        } else {
            throw std::runtime_error(std::string("entity not present in context: ")+name);
        }
    }


    void warnOmniChange(Entityptr context)
    {
        _senders.insert(context);
    }
    void warnEurusChange(Entityptr context)
    {
        _receivers.insert( context );
    }

    void update(){
        while(_senders.size() || _receivers.size()){

            if(_senders.size()){
                auto clone = _senders;
                auto context = this->shared_from_this();
                _senders.clear();
                for(auto& ent : clone){
                    ent->omniUpdate(context);
                }
            }
            if(_receivers.size()){
                auto clone = _receivers;
                auto context = this->shared_from_this();
                _receivers.clear();
                for(auto& ent : clone){
                    ent->eurusUpdate(context);
                }
            }

        }

    }

    static Entityptr getGlobal();

protected:
    Entity()
    {
    };

    template <class ...T>
    Entity(T...t)
    {
        addProcess(t...);
    };

    struct PlaceHolder {
        PlaceHolder(){
        }
    };

    template<class T>
    static PlaceHolder createGlobalEntity(){
        Entityptr novo = Entityptr(new T());
        auto global = Entity::getGlobal();
        global->addOmni(novo);
        global->addEurus( novo);

    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};

}
