
#pragma once
#include <unordered_map>
#include <memory>
#include "DataType/Datatype.h"
#include "DataType/DataPair.h"
//#include "ProcessBase.h"
namespace pg
{
class Data;
using Dataptr = std::shared_ptr<Data>;
struct Data : enable_shared_from_this_virtual<Data>
 {
    Data(){
    }
    Data(const Data& data){}


    virtual Datatypeptr getType() const=0;
    virtual std::string toString() const =0;
    //virtual Dataptr junction(  Dataptr other) const;

private:
};
using Dataptr = std::shared_ptr<Data>;


extern std::ostream& operator<<(std::ostream& os, const Dataptr& data );


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




