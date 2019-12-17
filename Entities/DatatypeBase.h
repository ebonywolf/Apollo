#pragma once

#include "Basic.h"
#include <string>
#include <memory>
#include <vector>
namespace pg{

using DataId = int;

class DatatypeBase;
using Datatypeptr = std::shared_ptr<const DatatypeBase>;
using ByteArray = std::vector<char>;
class HashKey;

class DatatypeBase : public enable_shared_from_this_virtual<DatatypeBase>
{
public:

   // virtual void join( Datatypeptr other) =0;
    virtual std::string toString() const=0;
    virtual Datatypeptr junction( Datatypeptr other)const =0;
    virtual Datatypeptr getHashKey() const=0;
    virtual Datatypeptr getFrom() const=0;
    virtual Datatypeptr getTo() const=0;
    virtual Datatypeptr getInverseDataPair()const=0;
    virtual Datatypeptr getDataPair()const=0;
    virtual bool contains(Datatypeptr)const=0;

   // virtual Datatypeptr getNull() const = 0;

    virtual bool equals(const Datatypeptr key) const{
        auto alce = toString();
        auto blce = key->toString();
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

//extern std::ostream& operator<<( std::ostream& os, const Datatypeptr me);

struct EditableDatatype : public DatatypeBase {
    virtual void join( const Datatypeptr other)=0;

};

}