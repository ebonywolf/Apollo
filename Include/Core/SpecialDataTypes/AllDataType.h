#pragma once

#include "DatatypeBase.h"

#include "Data/Data.h"
#include <functional>

namespace pg{

class AllType : public DatatypeBase, public Data {
public:
    virtual std::string toString() const{
        return "all";
    }
    virtual Datatypeptr junction( Datatypeptr other)const {
        return DatatypeBase::shared_from_this();
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
        return true;
    }

    virtual Datatypeptr getType() const{
         return get();
    }
    static std::shared_ptr<AllType> get(){
         static auto instance = std::make_shared<AllType>();
         return instance;
    }
    bool equals(const Datatypeptr key) const override{
        return false;
    }
    bool e_equals(const Datatypeptr key) const override{
        return false;
    }

};
extern decltype( std::bind(AllType::get) ) All;


}
