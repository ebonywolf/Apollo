
#pragma once
#include <unordered_map>
#include <memory>
#include "DataType/Datatype.h"
#include "DataType/DataPair.h"
//#include "ProcessBase.h"
namespace pg
{

struct Data : enable_shared_from_this_virtual<Data>
 {
    Data(){
    }
    Data(const Data& data){}


    virtual Datatypeptr getType() const=0;
    virtual std::string toString() const =0;

    friend std::ostream& operator<<(std::ostream& os, const Data& data )
    {
        os<<"Base Data:"<<data.getType();
        return os;
    }
private:
};
using Dataptr = std::shared_ptr<Data>;


extern std::ostream& operator<<(std::ostream& os, const Dataptr& data );

struct DataSet: public  Data {

    DataSet(Datatypeptr type):type(type){
    }

    void join( Dataptr other){
        _internal.push_back(other);
    }
    virtual std::string toString() const {
        std::string alce="";
        for(const auto& x: _internal){
            alce+= x->toString() += " | ";
        }
        if(_internal.empty())
            alce = "Empty set:"+type->toString();
        return alce;
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




