
#pragma once
#include "Datatype.h"
#include "Tools.h"

#include <memory>

namespace pg
{


struct Data //:protected std::unique_ptr<Base_Data>
 {
    Data():_id(id_cont++){

    }

    virtual Datatypeptr getType() const=0;

    friend std::ostream& operator<<(std::ostream& os, const Data& data )
    {
     //   os<<"Data:"<<data.getType();
        return os;
    }
    const long int _id;
    static long int id_cont;
};

template <class T>
struct GenericData: public Data {
    GenericData():GenericData(typeid(T).name())
    {
    }

    GenericData(std::string type_id):name_id(type_id)
    {
    }

    virtual Datatypeptr getType() const
    {
        throw "Todo";

    }

    friend std::ostream& operator<<(std::ostream& os, const GenericData<T>& data )
    {
   //     os<<"Data:"<<data.getType()<<":"<<data.get();

        return os;
    }
    std::string name_id;
};
using Dataptr = std::shared_ptr<Data>;

struct FutureBase: public Dataptr{
    FutureBase(Datatypeptr type):type(type){
    }
    virtual Datatypeptr getType() const
   {
       return type;
   }
    Datatypeptr type;
    Dataptr _actualObject;

};


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

namespace std
{
template <>
struct hash<pg::Datatype> {
    std::size_t operator()(const pg::Datatype& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.toString());

    }
};
template <>
struct hash<pg::DataPair> {
    std::size_t operator()(const pg::DataPair& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.toString());

    }
};
}




