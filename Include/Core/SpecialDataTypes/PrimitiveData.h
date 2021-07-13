#pragma once

#include "Data/GenericData.h"


namespace pg{

template <class T>
struct Primitive_Data : public pg::GenericData<T>{

    Primitive_Data(T val):val(val)
    {
    }
    Primitive_Data():Primitive_Data(0){}
    T getValue()
    {
        return val;
    }
    std::string toString() const
    {
       return std::to_string(val);
    }
    friend std::ostream& operator<<(std::ostream& os, const Primitive_Data<T>& data )
    {
        os<<data.val;
        return os;
    }
private:
    T val;
};

}
