#pragma once

#include "Data.h"
#include "MetaTools/GetObject.h"
namespace pg{


struct FutureBase: public Dataptr{
    FutureBase(Datatypeptr type):
        type(type)
    {
    }
    ~FutureBase(){}
    virtual Datatypeptr getType() const
    {
       return type;
    }
    Datatypeptr type;
    bool _ready=0;

   // Dataptr _actualObject;
    std::vector<Dataptr> _returnData;

};

//

struct Future : public std::shared_ptr<FutureBase>{

    //Future():std::shared_ptr<FutureBase>(new FutureBase()){}

    Future(Datatypeptr type):std::shared_ptr<FutureBase>(new FutureBase(type))
    {

    }

    void set(Dataptr d){
        auto alce = get();
        alce->_returnData.push_back(d);
    }
    std::vector<Dataptr> getData(){
        auto alce = get();

        return   alce->_returnData;
    }



    template <class T>
    T getObject(){
        if(!ready())throw "foo";

        T attr;
        Tools::getObject(attr,getData()[0] );
        return attr;
    }

    void setReady(){
        auto alce = get();
        alce->_ready = true;
    }

    bool ready(){
       auto alce = get();
       return alce->_ready;
    }
    virtual Datatypeptr getType() const
    {
        return get()->getType();
    }
private:


};

}


