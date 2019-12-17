
#pragma once
#include "Datatype.h"
#include "Tools.h"
#include <unordered_map>
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
        return std::make_shared<Datatype>(name_id);

    }

    friend std::ostream& operator<<(std::ostream& os, const GenericData<T>& data )
    {
   //     os<<"Data:"<<data.getType()<<":"<<data.get();

        return os;
    }
    std::string name_id;
};
using Dataptr = std::shared_ptr<Data>;



struct DataSet : public Data{

    DataSet(Datatypeptr type):type(type){
    }

    virtual Datatypeptr getType() const{
        return type;
    }

private:
     std::vector<Dataptr> _internal;
     Datatypeptr type;
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




