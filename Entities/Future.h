#pragma once

#include "Data.h"

namespace pg{


struct FutureBase: public Dataptr{
    FutureBase(Datatypeptr type):
        type(type)
    {
        _actualObject= std::make_shared<DataSet>(type);
    }
    virtual Datatypeptr getType() const
    {
       return type;
    }
    Datatypeptr type;
    Dataptr _actualObject;

};

//

struct Future : public std::shared_ptr<FutureBase>{

    //Future():std::shared_ptr<FutureBase>(new FutureBase()){}
    Future(Datatypeptr type):std::shared_ptr<FutureBase>(new FutureBase(type)){
    }
    void set(Dataptr p){
        if(ready())throw "foo";
        get()->_actualObject = p;
    }
    Dataptr getData(){
        auto alce = get();
        Dataptr data = alce->_actualObject;
        return  data;
    }

    template <class T>
    T getObject(){
        if(!ready())throw "foo";

        Dataptr data = get()->_actualObject;
        auto alce = data.get();
        T* t = dynamic_cast<T*>(alce);
        return *t;
    }

    bool ready(){
        if(get()->_actualObject)return true;
        return false;
    }
    virtual Datatypeptr getType() const
    {
        return get()->getType();
    }
};

}


