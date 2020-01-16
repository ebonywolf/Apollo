#pragma once
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

//

#include "DatatypeBase.h"
#include "KeySet.h"
#include "Tools.h"

namespace pg {


struct Datatype: public EditableDatatype
{ //defines dataTypes, not data itself
    static const Datatypeptr getNull(){
        static Datatypeptr nul = std::make_shared<Datatype>();
        return nul;
    }

    Datatype() :
            Datatype("null")
    {
    }
    Datatype(std::string _name):
        _key( std::make_shared<HashKey>(_name) )
    {
    }
    virtual bool contains(Datatypeptr d)const override{
        return _key->contains(d);
    }

    virtual void join( Datatypeptr other)override;

    virtual std::string toString() const override;
    virtual Datatypeptr getFrom() const override;
    virtual Datatypeptr getTo() const override;
    virtual Datatypeptr getHashKey() const override;
    virtual Datatypeptr getInverseDataPair()const override;
    virtual Datatypeptr getDataPair()const override;
    virtual Datatypeptr junction( Datatypeptr other)const override;


private:
    Datatypeptr _key;
};

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
        return std::make_shared<DataPair>(_from,_to);
    }

    virtual Datatypeptr getInverseDataPair()const  override{
        return std::make_shared<DataPair>(_to, _from);
    }
    virtual Datatypeptr getDataPair() const override{
        return std::make_shared<DataPair>(_from, _to);
    }
    virtual Datatypeptr getHashKey() const override{
        return _from->getHashKey() + _to->getHashKey();
    }

private:
    std::shared_ptr<const Datatype> _from,_to;
};

template <class FROM, class TO>
class GenericDataPair: public DataPair
{
public:
    GenericDataPair() :
            DataPair(getDataPair())
    {
    }
    DataPair getDataPair(){
        FROM from;
        TO to;
        Datatypeptr fromType(_getType(from));
        Datatypeptr toType(_getType(to));
        return DataPair(fromType, toType);
    }

};


struct DatapairSet:public  EditableDatatype  {

} ;








}

#endif // DATA_TYPE_H
