#pragma once

#include "Datatype.h"
#include "Identification/KeyChain.h"

namespace pg{


template <class ...T >
class VariadicDatatype: public DatatypeBase
{
public:
    VariadicDatatype():_key(createKey<T...>())
    {
    }
    ~VariadicDatatype(){

    }
    std::string toString() const{
        return _key->toString();
    }
    Datatypeptr junction( Datatypeptr other)const {
        return _key->junction(other);
    }
    Datatypeptr getHashKey() const{
        return _key;
    }
    Datatypeptr getFrom() const{
        return _key->getFrom();
    }
    Datatypeptr getTo() const{
        return _key->getTo();
    }
    Datatypeptr getInverseDataPair()const{
        return _key->getInverseDataPair();
    }
    Datatypeptr getDataPair()const{
        return _key->getDataPair();
    }
    bool contains(Datatypeptr d)const{
        return _key->contains(d);
    }

protected:
    KeyChainptr _key;
};

}
