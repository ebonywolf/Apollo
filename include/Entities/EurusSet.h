#pragma once
#ifndef EURUS_SET
#define EURUS_SET

#include "OmniSet.h"

namespace pg{




class EurusSet :  public Process_Base
 {
public:
    EurusSet();
    void extend(Processptr);
    virtual void handle(Entityptr ent, Packet d);
    virtual Future send(Dataptr sentData, const Datatypeptr fromType, Processptr context );
    virtual void omniUpdate(const Processptr context) ;
    virtual void eurusUpdate(const Processptr context);
    virtual void warnEurusChange(Processptr context);
    virtual void warnOmniChange(Processptr context);
    virtual void receiveData(Processptr context, Packet packet);

    virtual Processptr getEurus() const ;
    virtual Processptr getOmni() const ;
    virtual Processptr getOmni(Datatypeptr name) const ;
    virtual Processptr getBase() const ;

    virtual bool hasEurus(Datatypeptr) const;
    virtual bool hasOmni(Datatypeptr name) const;
    virtual int size() const ;
    virtual bool contains(Datatypeptr d)const override;


    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    using EurusType = std::unordered_map<Datatypeptr , OmniSet, HashFunction  >;
    KeySetptr _key;
    EurusType _internal;

};


}


#endif // EURUS_SET
