#pragma once

#include "Datatype.h"
namespace pg{

struct DataPair: public DatatypeBase
{
    DataPair() :
            DataPair(Datatype::getNull(), Datatype::getNull())
    {

    }
    DataPair(Datatypeptr from, Datatypeptr to):
    _from( std::static_pointer_cast<const Datatype>(from)),_to( std::static_pointer_cast<const Datatype>(to))
    {
    }
    virtual std::string toString() const override{
        return getHashKey()->toString();
    }
    virtual Datatypeptr getFrom() const override{
        return _from;
    }
    virtual Datatypeptr getTo() const override{
        return _to;
    }
    virtual bool contains(Datatypeptr d)const override{
        return _to->contains(d->getTo()) && _from->contains(d->getFrom());
    }

    virtual Datatypeptr junction( Datatypeptr other)const {
        Datatypeptr alce = getDataPair();
        auto _from = getFrom()->junction(other->getFrom());
        auto _to = getTo()->junction(other->getTo());
        return std::make_shared<DataPair>(_to, _from );
    }

    virtual Datatypeptr getInverseDataPair()const  override{
        return std::make_shared<DataPair>(_from ,_to );
    }
    virtual Datatypeptr getDataPair() const override{
        return std::make_shared<DataPair>(_to ,_from );
    }
    virtual Datatypeptr getHashKey() const override;

private:
    std::shared_ptr<const Datatype> _from,_to;
};

struct DatapairSet:public  EditableDatatype  {

} ;

}

