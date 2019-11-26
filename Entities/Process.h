
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <fstream>
#include <functional>
#include <iostream>

#include <json/json.h>
#include "Data.h"
#include "EntityBase.h"
namespace pg
{


class Entity;
class Process;
//using Processptr = std::shared_ptr<Process>;
class Process : public Process_Base{//Defines function
public:
    Process(){}


    virtual  Dataptr handle(std::shared_ptr<Entity> ent, Dataptr d) const {
        throw "foo";
        return 0;
    }


};


template<class INPUT, class OUTPUT>
struct GenericProcess: public Process {
    using Functiontype= std::function<OUTPUT(std::shared_ptr<Entity>,INPUT)>;

    template <class T>
    static GenericProcess* createProcess( OUTPUT(myfunc)( std::shared_ptr<T>, INPUT) ){
        //Creates new Process object with a function pointer as executer
        auto lambdaFunc = [myfunc](std::shared_ptr<Entity> entity, INPUT input ){
          std::shared_ptr<T> alce = std::dynamic_pointer_cast<T>(entity);
          return myfunc(alce, input);
      };
      auto novo = new GenericProcess<INPUT,OUTPUT>();
      novo->_func=lambdaFunc;
      return novo;
    }

    virtual Dataptr handle(std::shared_ptr<Entity> ent, Dataptr d) const override{
        INPUT* input = static_cast<INPUT*>(d.get());
        OUTPUT output =_func(ent, *input);
        return _getObj(output);
    }

private:
    GenericProcess():Process(GenericDataPair<INPUT,OUTPUT>())
    {
    }

    Functiontype _func;
};


}


namespace std
{
template <>
struct hash<pg::Process> {
    std::size_t operator()(const pg::Process& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.getHashKey()->toString());

    }
};
}

namespace pg
{





/*

template <class MY_TYPE>
struct Singleton: public Object<MY_TYPE>
{
    static std::shared_ptr<MY_TYPE> get( MY_TYPE* val=0  ){

        static std::shared_ptr<MY_TYPE> me;
        if(val){
            me.reset(val);
        }
        if(!me){
            me=std::make_shared<MY_TYPE>();
        }
        return me;
    }

protected:
    Singleton(){}

};

template <class MY_TYPE>
struct MultiInstance : public Object<MY_TYPE> {
     static std::shared_ptr<MY_TYPE> get(){
        //TODO guarantee cleanup
        return std::make_shared<MY_TYPE>();
    }
};


*/

}

