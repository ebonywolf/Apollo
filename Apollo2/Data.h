
#pragma once
#include "Datatype.h"


namespace pg
{

struct Base_Data {

};

struct Data : protected std::unique_ptr<Base_Data> {
    Data(){
    }

    virtual Datatype getType() const=0;
    friend std::ostream& operator<<(std::ostream& os, const Data& data )
    {
        os<<"Data:"<<data.getType();
        return os;
    }

};


template <class T>
struct GenericData: public Data {
    GenericData():GenericData(typeid(T).name())
    {
    }

    GenericData(std::string id):name_id(id)
    {
    }

    virtual Datatype getType() const
    {
        return Datatype(name_id);
    }

    friend std::ostream& operator<<(std::ostream& os, const GenericData<T>& data )
    {
        os<<"Data:"<<data.getType()<<":"<<data.get();

        return os;
    }
    std::string name_id;

};
;

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

        return hash<string>()(k.getName());

    }
};
template <>
struct hash<pg::DataPair> {
    std::size_t operator()(const pg::DataPair& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.getHashKey());

    }
};


}
