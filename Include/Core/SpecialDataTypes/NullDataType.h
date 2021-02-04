#pragma once

#include "DatatypeBase.h"
#include "DataType/Data.h"
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
        return this->shared_from_this();
    }
    virtual Datatypeptr getFrom() const{
        return this->shared_from_this();
    }
    virtual Datatypeptr getTo() const{
        return this->shared_from_this();
    }
    virtual Datatypeptr getInverseDataPair()const{
        return this->shared_from_this();
    }
    virtual Datatypeptr getDataPair()const{
        return this->shared_from_this();
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
};


extern decltype( std::bind(NullType::get) ) Null;

}
