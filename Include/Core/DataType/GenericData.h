#pragma once
#include "Data.h"

namespace pg {

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



template <class T>
struct Generic_GenericData : public T , public pg::GenericData<T>{
    Generic_GenericData(){}
    Generic_GenericData(const T& t):T(t){}

    using T::T;
};

}

