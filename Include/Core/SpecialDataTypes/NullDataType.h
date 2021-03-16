#pragma once

#include "DatatypeBase.h"
#include "Data/Data.h"
#include <functional>
namespace pg{


class NullType;

class NullType : public DatatypeBase, public Data{
public:

    virtual std::string toString() const{
        return "null";
    }
    virtual Datatypeptr junction( Datatypeptr other)const {
        return other;
    }
    virtual Datatypeptr getHashKey() const {
        return DatatypeBase::shared_from_this();
    }
    virtual Datatypeptr getFrom() const{
        return DatatypeBase::shared_from_this();
    }
    virtual Datatypeptr getTo() const{
        return DatatypeBase::shared_from_this();
    }
    virtual Datatypeptr getInverseDataPair()const{
        return DatatypeBase::shared_from_this();
    }
    virtual Datatypeptr getDataPair()const{
        return DatatypeBase::shared_from_this();
    }
    virtual bool contains(Datatypeptr)const{
        return false;
    }
    virtual Datatypeptr getType() const{
        return get();
    }
    static std::shared_ptr<NullType> get(){
        static auto instance = std::make_shared<NullType>();
        return instance;
    }
    bool equals(const Datatypeptr other) const override{
        return true;
    }
};

extern decltype( std::bind(NullType::get) ) Null;

}
