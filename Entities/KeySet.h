#pragma once

#include <set>
#include <string>
#include "Datatype.h"

namespace pg{


class HashKey: public DatatypeBase{
public:
    HashKey(){}
    HashKey(std::string value):value(value){

    }
    virtual std::string toString()const{
        return value;
    }
    /*
    DatatypeBase& operator+(const HashKey& key)const {
        if(*this < key ){
            return HashKey( value+"_"+key.value );
        }else{
            return HashKey( key.value+"_"+value );
        }
    }
    */

     virtual void join(Datatypeptr other);
     virtual Datatypeptr junction( Datatypeptr other)const ;
     virtual Datatypeptr getHashKey() const;
     virtual Datatypeptr getFrom() const;
     virtual Datatypeptr getTo() const;
     virtual Datatypeptr getInverseDataPair()const;
     virtual Datatypeptr getDataPair()const;



    friend std::ostream& operator<<(std::ostream& os, const HashKey& key )
    {
        os<<key.value;
        return os;
    }
private:
    std::string value;
};




class KeySet {
public:
    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;


private:
    std::set<std::string> keyset;
};


}



struct HashFunction{
    std::size_t operator()(const pg::Datatypeptr k) const{
        return  std::hash<std::string>()(k->toString());
    }
};



namespace std
{
template <>
struct hash<pg::HashKey> {
    std::size_t operator()(const pg::KeySet& k) const
    {
        return hash<string>()(k.toString());
    }
};


}
