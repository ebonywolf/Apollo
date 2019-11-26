#pragma once
#ifndef ENTITY_SET
#define ENTITY_SET

#include "EntityBase.h"

namespace pg{


struct EntityptrHash{
    std::size_t operator()(const pg::Processptr& k) const;
};

struct Entitycmp
{
  bool operator() (const Processptr& t1, const Processptr& t2) const;
};


struct AlceKey{
    std::size_t operator()(const pg::HashKey& k) const;
};



class OmniSet:  public Process_Base, public KeySet
{
public:
    void extend(Processptr);
    virtual Dataptr handle(Entityptr ent, Dataptr d) const ;
    virtual Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context );
    virtual void omniUpdate(const Processptr context) ;
    virtual void eurusUpdate(const Processptr context);
    virtual void warnEurusChange(Processptr context);
    virtual void warnOmniChange(Processptr context);
    virtual void receiveData(Processptr context, Packet packet);

    virtual Processptr getOmni() const ;
    virtual Processptr getOmni(Datatypeptr name) const ;
    virtual Processptr getNull() const ;

    virtual bool hasEurus(Datatypeptr) const;
    virtual bool hasOmni(Datatypeptr name) const;
    virtual int size() const ;

    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    using MapType = std::unordered_map<Datatypeptr ,Processptr, HashFunction  >;

    MapType _internal ;

};




class EurusSet :  public Process_Base
 {
public:
    void extend(Processptr);
    virtual Dataptr handle(Entityptr ent, Dataptr d) const ;
    virtual Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context );
    virtual void omniUpdate(const Processptr context) ;
    virtual void eurusUpdate(const Processptr context);
    virtual void warnEurusChange(Processptr context);
    virtual void warnOmniChange(Processptr context);
    virtual void receiveData(Processptr context, Packet packet);

    virtual Processptr getOmni() const ;
    virtual Processptr getOmni(Datatypeptr name) const ;
    virtual Processptr getNull() const ;

    virtual bool hasEurus(Datatypeptr) const;
    virtual bool hasOmni(Datatypeptr name) const;
    virtual int size() const ;

    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    using EurusType = std::unordered_map<Datatypeptr , OmniSet, HashFunction  >;

    EurusType _internal;

};


}


#endif // ENTITY_SET
