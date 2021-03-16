#pragma once
#include <unordered_map>
#include <unordered_set>

#include "Communication/Future.h"
#include "Data/Data.h"
#include "Data/DataTuple.h"
#include "Identification/KeySet.h"
#include "Base.h"
#include "MetaTools/GetData.h"
#include "MetaTools/GetType.h"

namespace pg
{

class Process_Base;
class EditableProcess;

using Entity_Base = EditableProcess;
using Processptr = std::shared_ptr<Process_Base>;
using Entityptr = std::shared_ptr<Entity_Base>;
using C_Entityptr = std::shared_ptr<const Entity_Base>;

class Packet;
class EntitySet;
class ProcessSet;
class DataPair;

struct Process_Base: public DatatypeBase,
        public enable_shared_from_this_virtual<Process_Base>
{
    virtual void handle(Entityptr ent, Packet d) = 0;
    virtual Future send(Dataptr sentData, const Datatypeptr fromType,
            Processptr context)=0;

    virtual void omniUpdate(const Processptr context) = 0;
    virtual void eurusUpdate(const Processptr context) = 0;
    virtual void warnEurusChange(const Processptr context) = 0;
    virtual void warnOmniChange(const Processptr context) = 0;
    virtual Processptr getOmni() const = 0;
    virtual Processptr getEurus() const = 0;
    virtual bool hasEurus(const Datatypeptr) const =0;
    virtual bool hasOmni(const Datatypeptr name) const =0;
    virtual Processptr getOmni(const Datatypeptr name) const = 0;
    virtual Processptr getBase() const = 0;
    virtual void extend(const Processptr other) = 0;
    virtual int size() const = 0;
    virtual void receiveData(const Processptr context, Packet packet)=0;

    template<class T, class D>
    Future send(D d)
    {
        Dataptr sentData = Tools::getData(d);
        Processptr context = shared_from_this();
        T received;
        const auto fromType = Tools::getType(received);
        return send(sentData, fromType, context);
    }
    template<class T, class ...D>
    Future send(D ... d)
    {
        auto sentData = std::make_shared<DataTuple<D...>>(d...);
        Processptr context = shared_from_this();
        T received;
        const auto fromType = Tools::getType(received);
        return send(sentData, fromType, context);
    }

    bool isNull() const
    {
        return this->size() == 0;
    }

    Processptr shared_from_this()
    {
        return enable_shared_from_this_virtual < Process_Base
                > ::shared_from_this();
    }
};

extern std::ostream& operator<<(std::ostream &os, const Processptr notme);

template<class T>
Entityptr cast(T ptr)
{
    return std::dynamic_pointer_cast<Entity_Base>(ptr);
}

struct EditableProcess: public Process_Base
{
    virtual void addOmni(const Processptr obj) = 0;
    virtual void addEurus(const Processptr obj) = 0;
    virtual void update() =0;
};

}
