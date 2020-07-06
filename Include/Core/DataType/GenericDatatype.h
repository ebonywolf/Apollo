#pragma once

#include "Datatype.h"
#include "MetaTools/GetType.h"

namespace pg{


template <class TO, class FROM >
class GenericDataPair: public DataPair
{
public:
    GenericDataPair() :
            DataPair(getDataPair())
    {
    }
    DataPair getDataPair(){
        FROM from;
        TO to;
        Datatypeptr fromType( Tools::getType(from));
        Datatypeptr toType( Tools::getType(to));
        return DataPair(toType, fromType );
    }

};

}
