#pragma once

#include <any>
#include "Specials.h"

namespace pg{


class Attributes{
public:
    using Keyset = std::unordered_set<std::string>;
    Attributes(){//TODO delete default cons
    };
    Attributes(Keyset keys):_keys(keys){}

protected:
    std::unordered_map<std::string, std::any> _values;
    Keyset _keys;
};


template <class MY_TYPE>
class Object: public Common<MY_TYPE>{
public:
    Object(){}
    template<class... T>
    Object(T&&... t ){
    }
private:
    template<class F, class... T>
    void __init(F&& f, T&&... t){
        std::string key = typeof(f);

        _attributes._keys.insert( typeof(f));
    }

    const Attributes _attributes;
};


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


template < class KEY ,class MY_TYPE>
struct MapInstance  {
     std::shared_ptr<MY_TYPE> at(KEY key){
        if(!instance_map[key]){
            instance_map[key] = std::make_shared<MY_TYPE>();
        }
        return  instance_map[key];
     }

private:
    std::unordered_map<KEY, std::shared_ptr<MY_TYPE>> instance_map;
};


struct Data: public std::any{
   // std::shared_ptr
};


template<class KEY, class TYPE>
class MatrixMap: public std::unordered_map<KEY, std::unordered_map<KEY,TYPE>>{

};

class GenericEntity;
using Generic_ptr = std::shared_ptr<GenericEntity> ;
using GenericFunction =  std::function< Data (Generic_ptr)>;

class GenericEntity{


    void addFunction(GenericFunction){
    }

};


struct GlobalFunctions: public MatrixMap<std::string,GenericFunction>, public Singleton<GlobalFunctions>
{


};
}
