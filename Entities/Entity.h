#pragma once

#include <fstream>
#include <future>
#include <iostream>
#include <json/json.h>
#include "Data.h"
#include "Process.h"
#include "Tools.h"
#include "EntityBase.h"

#include "Packet.h"
namespace pg
{

#define GLOBAL "_Global"



struct Entity : public Entity_Base  {//Defines object that runs many functions and has many dataTypes
    using ContextMap = std::unordered_map<std::string,Entityptr>;
    using SendBuffer = std::unordered_map<Entityptr, std::unordered_map<Entityptr,Packet>>;
    using PacketList = std::vector<Packet>;

    PacketMap _sentBuffer;
    PacketMap _receivedBuffer;
    ProcessSet _senders;
    ProcessSet _receivers;

   // SendBuffer _sentBuffer;
    ProcessSet _omni;
    EntitySet _eurus;

    template<class T,class D>
    Future send( D d  )
    {
        Dataptr sentData = _getObj(d);
       //  d;//
        Processptr context= this->shared_from_this();
        T received;
        const auto fromType = _getType(received) ;//received.getType();
        return send(sentData, fromType,context );
    }



    template <class INPUT,class D, class OUTPUT>
    void addProcess( OUTPUT(func)(D, INPUT) )
    {
        auto alce = GenericProcess<INPUT,OUTPUT>::createProcess(func);
        Processptr p = Processptr (  alce ) ;

        addEurus(p);
    }

    template <class INPUT, class D, class OUTPUT,class ...T>
    void addProcess(OUTPUT(func)(D, INPUT), T ...t)
    {
        addProcess(func);
        addProcess(t...);
    }

//    void handle(Entityptr, Packet p) override;

/*
    bool hasMethod(Datatype from, Datatype to) const
    {
        DataPair par (from,to);
        return hasEurus(par);
*/
    bool hasEurus( DataPair par ) const override
    {
        return  _eurus.contains(par);
    }

    bool hasOmni(std::string name) const override
    {
        return _omni.contains(name);
    }
    void addOmni(const Processptr obj) override
    {
        _omni.insert(obj);
    }

    void addEurus( const Processptr obj) override;
    void omniUpdate(const Processptr context)
    {
        auto packets = _sentBuffer.pull(context);
        for (auto& pack: packets) {
            auto thisPtr = this->shared_from_this();
            Entityptr enti = std::static_pointer_cast<Entity_Base>(thisPtr);
            Packet request(   enti, pack.data, pack.futureAnswer, pack.context);

            auto alce = pack.destination;
            (*alce).receiveData(context, request);
        }
    }
    void eurusUpdate(const Processptr context)
    {
        auto packets = _receivedBuffer.pull(context);

        for (auto& pack: packets) {
          //  auto handler =_eurus[pack.getChannel()];
            //TODO check first param
            throw "Really todo";
          //  handler->handle(this->shared_from_this(),pack);
        }
    }


    Dataptr handle(Entityptr ent, Dataptr d) const ;

    Future send(Dataptr sentData, const Datatype fromType, Processptr context ) override;


    ProcessSet getOmniList() const{
        return _omni;
    }


    void extend(Processptr other) override{
        addEurus(other);
        for(auto ent: other->getOmniList())
        {
            addOmni(ent);
        }
    }

    /*
    {
        throw "Its actually pure virtual method, it must be extended";
    }
    */

    Processptr getOmni(std::string name) const override
    {
        if(_omni.contains(name)) {
            return _omni.get(name);
        } else {
            throw std::runtime_error(std::string("entity not present in context: ")+name);
        }
    }


    void warnOmniChange(Processptr context) override
    {
        _senders.insert(context);
    }
    void warnEurusChange(Processptr context) override
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
    void receiveData(Processptr context, Packet packet) override
    {
        //TODO MEMORY FUNCTION
        _receivedBuffer.push(context, packet);
        context->warnEurusChange(this->shared_from_this());
    }


protected:
    Entity()
    {
    };

    /* Todo, make this work
    template <class ...T>
    Entity(T...t)
    {
        addProcess(t...);
    };
    */

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
        return PlaceHolder();
    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};

using Particle = std::shared_ptr<Entity>;


}
