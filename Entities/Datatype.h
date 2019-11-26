#pragma once
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
#include <memory>
#include <vector>
#include "Basic.h"
namespace pg {

using DataId = int;

class DatatypeBase;
using Datatypeptr = std::shared_ptr<DatatypeBase>;
using ByteArray = std::vector<char>;
class HashKey;

class DatatypeBase
{
public:

    virtual std::string toString() const=0;
    virtual Datatypeptr junction( Datatypeptr other)const =0;
    virtual Datatypeptr getHashKey() const=0;
    virtual Datatypeptr getFrom() const=0;
    virtual Datatypeptr getTo() const=0;
    virtual Datatypeptr getInverseDataPair()const=0;
    virtual Datatypeptr getDataPair()const=0;

    virtual bool equals(const Datatypeptr key) const{
        return toString() == key->toString();
    }
    /*
    virtual bool operator<(const Datatypeptr key) const{
        return toString() < key->toString();
    }
    */
    friend std::ostream& operator<<(std::ostream& os, const DatatypeBase& data){
        os << data.toString();
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Datatypeptr data){
        os << data->toString();
        return os;
    }

};

extern bool operator==(const Datatypeptr me, const Datatypeptr notme);
extern Datatypeptr operator+(const Datatypeptr me, const Datatypeptr notme);

struct Datatype: public DatatypeBase, public enable_shared_from_this_virtual<DatatypeBase>
{ //defines dataTypes, not data itself
    static const Datatypeptr NULL_DATA;

    Datatype() :
            Datatype("null")
    {
    }
    Datatype(std::string name) :
        _key(name)
    {
    }
    virtual std::string toString() const override;
    virtual Datatypeptr getFrom() const override;
    virtual Datatypeptr getTo() const override;

    virtual Datatypeptr getHashKey() const override;
    virtual Datatypeptr getInverseDataPair()const override;
    virtual Datatypeptr getDataPair()const override;


    virtual Datatypeptr junction( Datatypeptr other)const override;

private:
    std::string _key;
};

struct DataPair: public Datatype
{
    DataPair() :
            DataPair(Datatype::NULL_DATA, Datatype::NULL_DATA)
    {
    }
    DataPair(Datatypeptr from, Datatypeptr to) :
            from(from), to(to)
    {
    }
    virtual std::string toString() const override{
        return getHashKey()->toString();
    }
    virtual Datatypeptr getFrom() const override{
        return from;
    }
    virtual Datatypeptr getTo() const override{
        return to;
    }


    virtual Datatypeptr junction( Datatypeptr other)const {
        Datatypeptr alce = getDataPair();
        auto _from = getFrom()->junction(other->getFrom());
        auto _to = getTo()->junction(other->getTo());
        return std::make_shared<DataPair>(_from,_to);
    }

    virtual Datatypeptr getInverseDataPair()const  override{
        return std::make_shared<DataPair>(to, from);
    }
    virtual Datatypeptr getDataPair() const override{
        return std::make_shared<DataPair>(from, to);
    }
    virtual Datatypeptr getHashKey() const override{
        return from->junction(to);
    }

private:
    Datatypeptr from, to;
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

}

#endif // DATA_TYPE_H
