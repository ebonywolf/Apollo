
#pragma once
#include <unordered_map>
#include <memory>
#include "Datatype.h"

namespace pg
{

struct Data //:protected std::unique_ptr<Base_Data>
 {
    Data():_id(id_cont++){

    }
    Data(const Data& data):_id(data._id){
    }



    virtual Datatypeptr getType() const=0;

    friend std::ostream& operator<<(std::ostream& os, const Data& data )
    {
     //   os<<"Data:"<<data.getType();
        return os;
    }
private:
    long int _id;
    static long int id_cont;
};
using Dataptr = std::shared_ptr<Data>;


struct DataSet {

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




