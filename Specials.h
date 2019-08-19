#pragma once
#include <memory>

namespace pg
{

//#define _ptr(X) std::shared_ptr<X>


template <class MY_TYPE>
struct Common{
    template<class T>
    static std::shared_ptr<MY_TYPE> getRoot(T t)
    {
        return std::static_pointer_cast<MY_TYPE>(t);
    }
};

struct Void{
};


template <class T>
class BinaryType: public T{
    bool _sign;
    bool sign(){return _sign;}
};

template <class T>
struct Positive{
    T get(){
        static T t;
        return t;
    }
};

template <class T>
struct Negative{
     T get(){
        static T t;
        return t;
    }
};


template <class MY_TYPE>
struct Singleton: public Common<MY_TYPE>
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
struct MultiInstance : public Common<MY_TYPE> {
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



}
