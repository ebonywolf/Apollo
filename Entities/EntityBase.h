
#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Basic.h"
#include "Data.h"
#include "KeySet.h"

namespace pg{



class Process_Base;
class Entity_Base;
using Processptr = std::shared_ptr<Process_Base>;
using Entityptr = std::shared_ptr<Entity_Base>;
using C_Entityptr = std::shared_ptr<const Entity_Base>;

class Packet;
class EntitySet;
class ProcessSet;
class DataPair;



struct Process_Base : public  DatatypeBase, public enable_shared_from_this_virtual<Process_Base>
{
    virtual Dataptr handle(Entityptr ent, Dataptr d) const =0;
    virtual Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context )=0;

    virtual void omniUpdate(const Processptr context) = 0;
    virtual void eurusUpdate(const Processptr context) = 0;
    virtual void warnEurusChange(Processptr context) = 0;
    virtual void warnOmniChange(Processptr context) = 0;
    virtual Processptr getOmni() const = 0;
    virtual Processptr getNull() const = 0;
    virtual bool hasEurus(Datatypeptr ) const=0;
    virtual bool hasOmni(Datatypeptr name) const =0;
    virtual Processptr getOmni(Datatypeptr name) const = 0;

    virtual void extend(Processptr other) = 0;
    virtual int size() const = 0;
    virtual void receiveData(Processptr context, Packet packet)=0;
};


template <class T>
Entityptr cast(T ptr){
    return std::dynamic_pointer_cast<Entity_Base>(ptr);
}

struct Entity_Base : public Process_Base {
    virtual void addOmni(const Processptr obj) = 0;
    virtual void addEurus( const Processptr obj) = 0;
    virtual void update() =0;
};




}
