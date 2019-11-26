#pragma once

#include <fstream>
#include <future>
#include <iostream>
#include <json/json.h>
#include "Data.h"
#include "Process.h"
#include "Tools.h"
#include "EntitySet.h"

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
    Processptr _senders;
    Processptr _receivers;

   // SendBuffer _sentBuffer;
    Processptr _omni;
    Processptr _eurus;

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

    Processptr getOmni(Datatypeptr name) const{
                return _omni->getOmni(name);
    }
    bool hasEurus( Datatypeptr par ) const override
    {
        return  _eurus->hasEurus(par);
    }

    bool hasOmni(Datatypeptr name) const override
    {
        return _omni->hasOmni(name);
    }

    void addOmni(const Processptr obj) override
    {
        _omni->extend(obj);
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

    Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context ) override;


    Processptr getOmniList() const{
        return _omni;
    }


    void extend(Processptr other) override{
        addEurus(other);

        addOmni(other->getOmni());

    }

    void warnOmniChange(Processptr context) override
    {
        _senders->extend(context);
    }
    int size() const override{
        return _receivers->size() + _senders->size();
    }
    void warnEurusChange(Processptr context) override
    {
        _receivers->extend( context );
    }
    Processptr getOmni() const override
    {
        return _omni;
    }
    void update(){


        while(_senders->size() || _receivers->size()){

            if(_senders->size()){
                auto clone = _senders;
                auto context = this->shared_from_this();
                _senders = _senders->getNull();
                clone->omniUpdate(context);

            }
            if(_receivers->size()){
                auto clone = _receivers;
                auto context = this->shared_from_this();
                _receivers = _receivers->getNull();
                clone->eurusUpdate(context);
            }

        }

    }

    static Entityptr getGlobal();

    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

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
        _eurus = std::make_shared<EurusSet>();
        _omni = std::make_shared<OmniSet>();
        _senders = std::make_shared<OmniSet>();
        _receivers = std::make_shared<OmniSet>();
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
