#pragma once
#include <memory>
#include "Entity.h"

namespace pg
{


template <class MY_TYPE>
struct Singleton
{
    static std::shared_ptr<MY_TYPE> get(){
        static std::shared_ptr<MY_TYPE> me;
        if(!me){
            me=std::make_shared<MY_TYPE>();
        }
        return me;
    }

/*
    template <typename  NOT_MY_TYPE>
    static decltype(auto) getFromMe(NOT_MY_TYPE notme ){
        using ReturnType = std::shared_ptr< Entity<decltype(notme->outputType()),MY_TYPE  > > ;
        auto me = get();
       ReturnType alsoMe = std::static_pointer_cast<ReturnType>(get());
        return alsoMe;
    }
    */

protected:
    Singleton(){}

   // static T* CreateInstance();
};



}
