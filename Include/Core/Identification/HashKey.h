#pragma once


#include "DatatypeBase.h"
#include <string>
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




}
