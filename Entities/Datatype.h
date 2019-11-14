#pragma once
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
namespace pg
{

using DataId = int;

struct Datatype { //defines dataTypes, not data itself

    static const Datatype NULL_DATA;

    Datatype():name("null")
    {
    }
    Datatype(std::string name):name(name)
    {
    }
    bool operator==(const Datatype& other)const
    {
        return name == other.name;
    }
    bool operator<(const Datatype& other)const
    {
        return name < other.name;
    }
    std::string getName()const
    {
        return name;
    };
    friend std::ostream& operator<<(std::ostream& os, const Datatype& data )
    {
        os<<data.name;
        return os;
    }
private:
    std::string name;
};

struct DataPair {
    DataPair() {}
    DataPair(Datatype from, Datatype to):from(from),to(to)
    {
    }
    Datatype getFrom()const
    {
        return from;
    }
    Datatype getTo()const
    {
        return to;
    }
    DataPair getInverse(){
        return DataPair(to,from);
    }

    std::string getHashKey()const
    {
        if(to < from) {
            return to.getName() + from.getName() ;
        } else {
            return from.getName() + to.getName() ;
        }
    }
    bool operator==(const DataPair& other)const
    {
        return getHashKey() == other.getHashKey();
    }
    friend std::ostream& operator<<(std::ostream& os, const DataPair& data )
    {
        os<<data.getHashKey();
        return os;
    }
private:
    Datatype from,to;
};

template <class FROM,class TO>
class GenericDataPair:  public DataPair{
public:
    GenericDataPair():DataPair(getDataPair()) {
    }

    DataPair getDataPair(){
        FROM from;
        TO to;
        Datatype fromType(from.getType());
        Datatype toType(to.getType());
        return DataPair(fromType, toType);
    }

};



}



#endif // DATA_TYPE_H
