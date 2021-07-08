#pragma once



#include "DatatypeBase.h"
#include "Data/Data.h"
#include <functional>

namespace pg{

template <class T>
class SetData : public DatatypeBase, public Data{
public:

    virtual std::string toString() const{
        return "null";
    }
    virtual Datatypeptr junction( Datatypeptr other)const {
        throw "Todo";
    }
    virtual Datatypeptr getHashKey() const {
        throw "Todo";
    }
    virtual Datatypeptr getFrom() const{
        throw "Todo";
    }
    virtual Datatypeptr getTo() const{
        throw "Todo";
    }
    virtual Datatypeptr getInverseDataPair()const{
        throw "Todo";
    }
    virtual Datatypeptr getDataPair()const{
       throw "Todo";
    }
    virtual bool contains(Datatypeptr other)const{
        throw "Todo";
    }
    virtual Datatypeptr getType() const{
        return DatatypeBase::shared_from_this();
    }
    static std::shared_ptr<SetData> get(){
        throw "Todo";
    }
};

extern decltype( std::bind(SetData::get) ) Any;

}
