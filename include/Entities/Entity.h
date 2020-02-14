#pragma once

#include <fstream>
#include <future>
#include <iostream>
#include <json/json.h>
#include "Data.h"
#include "Process.h"

#include "DatatypeBase.h"
#include "OmniSet.h"
#include "EurusSet.h"

#include "Packet.h"
#include "GenericProcess.h"
#include "VariadicProcess.h"
#include "MetaTools/Tools.h"

#include "MetaTools/GetType.h"

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
        Dataptr sentData = Tools::getData(d);
       //  d;//
        Processptr context= shared_from_this();
        T received;
        const auto fromType = Tools::getType(received) ;//received.getType();
        return send(sentData, fromType,context );
    }
     template<class T,class ...D>
     Future send( D... d  )
     {
        // Dataptr sentData = Tools::getData(d);
         auto sentData = std::make_shared<DataTuple<D...>>(d...);
        //  d;//
         Processptr context= shared_from_this();
         T received;
         const auto fromType = Tools::getType(received) ;//received.getType();
         return send(sentData, fromType,context );
     }

    template <class  OUTPUT,class D, class ...INPUT >
    void addProcess( OUTPUT(func)(D, INPUT...) )
    {
        auto alce = VariadicProcess< OUTPUT ,INPUT... >::createProcess(func);
        Processptr p = Processptr (  alce ) ;
        addEurus(p);
    }

    template <class  OUTPUT,class D, class INPUT >
    void addProcess( OUTPUT(func)(D, INPUT) )
    {
        auto alce = GenericProcess< OUTPUT ,INPUT >::createProcess(func);
        Processptr p = Processptr (  alce ) ;
        addEurus(p);
    }

    template <class OUTPUT , class D, class INPUT,class ...T>
    void addProcess(OUTPUT(func)(D, INPUT), T ...t)
    {
        addProcess(func);
        addProcess(t...);
    }

    Processptr getOmni(Datatypeptr name) const{
        return _omni->getOmni(name);
    }
    bool hasEurus(  const Datatypeptr par ) const override
    {
        return  _eurus->hasEurus(par);
    }

    bool contains(Datatypeptr d)const override
    {
        return _eurus->contains(d);
    }

    bool hasOmni(const Datatypeptr name) const override
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
            _omni->receiveData(context,pack);
            //TODO optimize this
        }
    }

    void eurusUpdate(const Processptr context)
    {
        auto packets = _receivedBuffer.pull(context);

        for (auto& pack: packets) {

            Entityptr me = std::static_pointer_cast<Entity_Base>(this->shared_from_this());
            handle( me , pack);
            pack.futureAnswer.setReady();

        }
    }


    void handle(Entityptr ent, Packet d) ;
    Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context ) override;


    Processptr getEurus() const override{
        return _eurus;
    }

    void extend(const Processptr other) override{


        addEurus(other);

        addOmni(other->getOmni());
    }

    void warnOmniChange(const Processptr context) override;
    int size() const override{
        return _receivers->size() + _senders->size();
    }
    void warnEurusChange(const Processptr context) override
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
                _senders = _senders->getBase();
                clone->omniUpdate(context);

            }
            if(_receivers->size()){
                auto clone = _receivers;
                auto context = this->shared_from_this();
                _receivers = _receivers->getBase();
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
    void receiveData(const Processptr context, Packet packet) override
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

    template <class ...T>
    Entity(T...t):Entity()
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
        std::cout<< "Adding to Global:"<<novo->toString() << std::endl;
        global->addOmni(novo);
        global->addEurus( novo);
        return PlaceHolder();
    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};



}
