#pragma once
#include <type_traits>
#include "SpecialDataTypes/AllDataType.h"
#include "Basic.h"

namespace pg{



template<class T>
class PrimitiveEntity : public MultiInstance<PrimitiveEntity<T>>{
public:
    PrimitiveEntity(T value ):
        MultiInstance<PrimitiveEntity<T>>(typeid(T).name(), valueFunction ),
        data(value)
    {
    }
    PrimitiveEntity( ):
          MultiInstance<PrimitiveEntity<T>>(typeid(T).name(), valueFunction )
      {
      }
    Primitive_Data<T> data;

    static Primitive_Data<T> valueFunction(pg::Entityptr me, pg::AllType all){
        auto realme  =  cast<PrimitiveEntity<T>>(me);
        return realme->data;
    }
    static_assert(std::is_fundamental<T>::value, "PrimitiveEntity can only inherit primitive types");



};

}
