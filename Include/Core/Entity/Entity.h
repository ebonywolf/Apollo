#pragma once


#include <fstream>
#include <future>
#include <iostream>

#include "MetaTools/GetData.h"
#include "MetaTools/GetObject.h"

#include "Process/VariadicProcess.h"

#include "ProcessBase.h"
#include "Data/DataTuple.h"
#include "Communication/Packet.h"

#include "Sets/EurusSet.h"
#include "Tools/Logger.h"
namespace pg
{

#define GLOBAL "_Global"

using Entity_Base = EditableProcess;

struct Entity : public Entity_Base {//Defines object that runs many functions and has many dataTypes
    using ContextMap = std::unordered_map<std::string,Entityptr>;
    using SendBuffer = std::unordered_map<Entityptr, std::unordered_map<Entityptr,Packet>>;
    using PacketList = std::vector<Packet>;

    ///Communication
    PacketMap _sentBuffer;
    PacketMap _receivedBuffer;
    Processptr _senders;
    Processptr _receivers;

    ///Self
    Processptr _omni;
    Processptr _eurus;

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

    template <class  OUTPUT,class D, class ...INPUT,class ...T>
	void addProcess(OUTPUT(func)(D, INPUT...), T ...t)
	{
    	addProcess(func);
    	addProcess(t...);
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

            Entityptr me = std::static_pointer_cast<Entity_Base>(shared_from_this());
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
                _senders = _senders->getBase();
                clone->omniUpdate(shared_from_this());

            }
            if(_receivers->size()){
                auto clone = _receivers;
                _receivers = _receivers->getBase();
                clone->eurusUpdate(shared_from_this());
            }
        }

    }

    static Entityptr getGlobal();


    virtual Datatypeptr getType() const{
        return getEurus();
    }
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

        context->warnEurusChange(shared_from_this());
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
        Entityptr novo = T::get();
        auto global = Entity::getGlobal();
        global->addOmni(novo);
        global->addEurus( novo);
        return PlaceHolder();
    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};



}
