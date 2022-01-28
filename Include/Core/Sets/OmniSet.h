#pragma once
#ifndef OMNI_SET
#define OMNI_SET

#include <ProcessBase.h>

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



class OmniSet:  public Process_Base
{
public:
    OmniSet();

    void extend(Processptr);
    virtual void handle(Entityptr ent, Packet d) ;
    virtual Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context );
    virtual void omniUpdate(const Processptr context) ;
    virtual void eurusUpdate(const Processptr context);
    virtual void warnEurusChange(Processptr context);
    virtual void warnOmniChange(Processptr context);
    virtual void receiveData(Processptr context, Packet packet);

    virtual Processptr getOmni() const ;
    virtual Processptr getEurus() const ;
    virtual Processptr getOmni(Datatypeptr name) const ;
    virtual Processptr getBase() const ;

    virtual bool hasEurus(Datatypeptr) const;
    virtual bool hasOmni(Datatypeptr name) const;
    virtual int size() const ;
    virtual bool isNull() const;

    virtual void join( Datatypeptr other) ;
    virtual bool contains(Datatypeptr d)const override;

    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    using MapType = std::unordered_map<Datatypeptr ,Processptr, HashFunction,HashCmp  >;
    KeySetptr _key;
    MapType _internal ;

};




}


#endif // OMNI_SET
