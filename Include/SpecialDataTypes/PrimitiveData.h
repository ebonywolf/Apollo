#pragma once

#include "DataType/GenericData.h"


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
private:
    T val;
};

}
