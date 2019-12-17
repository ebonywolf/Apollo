#pragma once

#include <set>
#include <string>

#include <map>
#include <iostream>
#include "DatatypeBase.h"
namespace pg{


class HashKey: public DatatypeBase{
public:
    HashKey(){}
    HashKey(std::string value) :
            value(value)
    {
    }
    virtual ~HashKey(){
    }
    std::string toString() const{

        return value;
    }
    virtual bool contains(Datatypeptr d)const override;

    virtual Datatypeptr junction(Datatypeptr other) const;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair() const;
    virtual Datatypeptr getDataPair() const;

    friend std::ostream& operator<<(std::ostream& os, const HashKey& key){
        os << key.value;
        return os;
    }
private:
    std::string value;
};




class KeySet: public EditableDatatype {
public:
    KeySet(){
    }
    virtual ~KeySet(){}
    virtual void join(const Datatypeptr other);

    virtual bool contains(Datatypeptr d)const override;

    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    std::map<std::string, Datatypeptr> _internal;
};
using KeySetptr = std::shared_ptr<KeySet>;


}


struct HashFunction{
    std::size_t operator()(const pg::Datatypeptr k) const{
        std::string alce = k->toString() ;
        return  std::hash<std::string>()(k->toString());
    }
};
struct HashCmp
{
  bool operator() (const pg::Datatypeptr& t1, const pg::Datatypeptr& t2) const{
      return t1->equals(t2);
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
