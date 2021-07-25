#pragma once

#include "Data/DataSet.h"
#include "MetaTools/GetObject.h"
namespace pg{


struct FutureBase{
    FutureBase(Datatypeptr type):
        type(type),_returnData(new DataSet(type))
    {

    }
    ~FutureBase(){}
    virtual Datatypeptr getType() const
    {
       return type;
    }
    Datatypeptr type;
    bool _ready=0;

    std::shared_ptr<DataSet> _returnData;

};


struct Future : public std::shared_ptr<FutureBase>, public DatatypeBase{

    Future(Datatypeptr type):std::shared_ptr<FutureBase>(new FutureBase(type))
    {
    }

    void set(Dataptr d)
    {
        auto me = get();
        me->_returnData->join(d);
    }

    Dataptr getData() const
    {
        auto alce = get();
        return alce->_returnData;
    }


    void setReady()
    {
        auto alce = get();
        alce->_ready = true;
    }

    bool ready() const
    {
       auto alce = get();
       return alce->_ready;
    }
    virtual Datatypeptr getType() const
    {
        return get()->getType();
    }

    virtual std::string toString() const
    {
    	return getType()->toString();
    }
    virtual Datatypeptr junction( Datatypeptr other)const
    {
    	return getType()->junction(other);
    }
    virtual Datatypeptr getHashKey() const
    {
    	return getType()->getHashKey();
    }
    virtual Datatypeptr getFrom() const
    {
    	return getType()->getFrom();
    }
    virtual Datatypeptr getTo() const
    {
    	return getType()->getTo();
    }
    virtual Datatypeptr getInverseDataPair()const
    {
    	return getType()->getInverseDataPair();
    }
    virtual Datatypeptr getDataPair()const
    {
    	return getType()->getDataPair();
    }
    virtual bool contains(Datatypeptr d)const
    {
    	return getType()->contains(d);
    }
private:


};

}


