#pragma once
#include <memory>

namespace pg
{

//#define _ptr(X) std::shared_ptr<X>


template<typename T>
struct enable_shared_from_this_virtual;

class enable_shared_from_this_virtual_base : public std::enable_shared_from_this<enable_shared_from_this_virtual_base>
{
    typedef std::enable_shared_from_this<enable_shared_from_this_virtual_base> base_type;
    template<typename T>
    friend struct enable_shared_from_this_virtual;

    std::shared_ptr<enable_shared_from_this_virtual_base> shared_from_this()
    {
        return base_type::shared_from_this();
    }
    std::shared_ptr<enable_shared_from_this_virtual_base const> shared_from_this() const
    {
       return base_type::shared_from_this();
    }

};

template<typename T>
struct enable_shared_from_this_virtual: virtual enable_shared_from_this_virtual_base
{
    typedef enable_shared_from_this_virtual_base base_type;

public:
    std::shared_ptr<T> shared_from_this()
    {
       std::shared_ptr<T> result(base_type::shared_from_this(), static_cast<T*>(this));
       return result;
    }

    std::shared_ptr<T const> shared_from_this() const
    {
        std::shared_ptr<T const> result(base_type::shared_from_this(), static_cast<T const*>(this));
        return result;
    }
};


template <class MY_TYPE>
struct Common: public enable_shared_from_this_virtual<MY_TYPE>{

    template<class T>
    static std::shared_ptr<MY_TYPE> getRoot(T t)
    {
        return std::static_pointer_cast<MY_TYPE>(t);
    }

   // template<class T>
    std::shared_ptr<MY_TYPE> getRoot(){
    //    return std::static_pointer_cast<MY_TYPE>(t);
        return  std::static_pointer_cast<MY_TYPE>( this->shared_from_this() );
             //   enable_shared_from_this_virtual<MY_TYPE>::shared_from_this();
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
