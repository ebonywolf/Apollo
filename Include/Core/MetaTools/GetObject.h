#pragma once

#include "SpecialDataTypes/PrimitiveData.h"

namespace Tools{




template <class T>
void _getObject_normal(std::shared_ptr<T>& attributer, pg::Dataptr data, std::true_type){
    attributer.swap(data);
}


template <class T>
void _getObject_normal(T& attributer,  pg::Dataptr data, std::true_type)
{
     T* result = dynamic_cast<T*>(data.get());
     attributer = *result;
}

template <class T>
void _getObject_normal(T& attributer,  pg::Dataptr data,std::false_type){
    std::shared_ptr<pg::Generic_GenericData<T>> genericData = std::dynamic_pointer_cast<pg::Primitive_Data<T>>(data);
    attributer = *genericData.get();
}


template <class T>
void _getObject_primitive(T& attributer,  pg::Dataptr data, std::true_type){

    std::shared_ptr< pg::Primitive_Data<T>> primitivePtr = std::dynamic_pointer_cast<pg::Primitive_Data<T>>(data);
    attributer = primitivePtr->getValue();
}

template <class T>
void _getObject_primitive(T& attributer,  pg::Dataptr data, std::false_type){
     return _getObject_normal(attributer,data, std::is_base_of<pg::Data,T>());

}


template <class T>
void _getObject(T& attributer,  pg::Dataptr data)
{
    _getObject_primitive(attributer, data, std::is_fundamental<T>());
}


template <class T, class D>
void _getObject(std::shared_ptr<D>& attributer,  pg::Dataptr data)
{
    D* alce =attributer.get();
    _getObject(*alce, data);
}



template <class T>
void getObject(T& attributer,  pg::Dataptr data)
{
    _getObject<T>(attributer, data);
}
/*
    template <class T,class D>
    T _get(std::shared_ptr<D> placeholder)
    {
       auto alce = getData();
       Dataptr alceptr = alce[0];
       T result;
       _castPtr(result, alceptr);
       // T t = _deref<alceptr.get()>(alceptr.get())
       return result;
    }
*/

}
