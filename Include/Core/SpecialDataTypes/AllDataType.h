#pragma once

#include "DatatypeBase.h"

#include "DataType/Data.h"
#include <functional>

namespace pg{

class AllType : public DatatypeBase, public Data {
public:
    virtual std::string toString() const{
        return "all";
    }
    virtual Datatypeptr junction( Datatypeptr other)const {
        return this->shared_from_this();
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
        return true;
    }
    virtual Datatypeptr getType() const{
         return get();
    }
    static std::shared_ptr<AllType> get(){
         static auto instance = std::make_shared<AllType>();
         return instance;
    }
};
extern decltype( std::bind(AllType::get) ) All;
}
