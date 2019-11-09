
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <fstream>
#include <functional>
#include <iostream>

#include <json/json.h>
#include "Data.h"
namespace pg
{

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
struct enable_shared_from_this_virtual: virtual enable_shared_from_this_virtual_base {
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
/////////////////////////////

class Process;
using Processptr = std::shared_ptr<Process>;
class Process : public DataPair {//Defines function
public:
    Process( )
    {
    }
    Process(const DataPair& data):
        DataPair(data)
    {
    }
    operator DataPair() const
    {
        return *this;
    }

    virtual Dataptr process(Dataptr)const{
        throw "foo";
        return 0;
    }


};

template<class INPUT, class OUTPUT>
struct GenericProcess: Process {

    GenericProcess(std::function<OUTPUT(INPUT)> func):Process(GenericDataPair<INPUT,OUTPUT>()),func(func)
    {
    }
    Dataptr process(Dataptr d) const {
        INPUT* input = static_cast<INPUT*>(d.get());
        OUTPUT output =func(*input);
        return std::make_shared<OUTPUT>(output);
    }

private:

    std::function<OUTPUT(INPUT)> func;

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
        return hash<string>()(k.getHashKey());

    }
};
}

namespace pg
{


class Entity;
using Entityptr = std::shared_ptr<Entity>;
using C_Entityptr = std::shared_ptr<const Entity>;

struct ProcessptrHash{
    std::size_t operator()(const pg::Processptr& k) const
    {
        if(!k)throw "foo";
        return std::hash<std::string>()(k->getHashKey());
    }
};
struct Processcmp
{
  bool operator() (const Processptr& t1, const Processptr& t2) const{
      t1->getHashKey() == t2->getHashKey();
  }
};



class ProcessList :public std::unordered_set<Processptr,ProcessptrHash,Processcmp >
{
public:
    ProcessList()
    {
    }
    bool count(Processptr alce)const{
        std::cout<< "Size:"<<size() << std::endl;
        std::cout<< "Alce"<< *alce.get() << std::endl;
        for (auto x: *this) {
            std::cout<< *x.get() << std::endl;
        }
        bool a  = unordered_set::count(alce);

        return a ;
    }
    Processptr get(DataPair datahash)const{
           Processptr alce = std::make_shared<Process>(datahash);
           return *find(alce);
    }

    bool count(DataPair datahash)const{
        Processptr alce = std::make_shared<Process>(datahash);
        return count(alce);
    }

private:


};



/*
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


*/

}

