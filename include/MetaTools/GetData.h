#pragma once
#include "Entities/GenericData.h"

namespace Tools {


template <class T>
pg::Dataptr _getData_normal(T& t, std::true_type)
{
    return pg::Dataptr(new T(t));
}

template <class T>
pg::Dataptr _getData_normal(T& t,std::false_type)
{
    return pg::Dataptr(new  pg::Generic_GenericData<T>(t));
}


template <class T>
pg::Dataptr _getData_primitive(T& t, std::true_type)
{
    return std::make_shared< pg::Primitive_Data<T>>(t);
}

template <class T>
pg::Dataptr _getData_primitive(T& t,std::false_type)
{
   return _getData_normal(t, std::is_base_of<pg::Data,T>());
}

template <class T>
pg::Dataptr getData(std::shared_ptr<T> t){
    return std::static_pointer_cast<pg::Data>(t);
}

/*
template <class T>
pg::Dataptr  _getObj(T& t){

    std::shared_ptr<pg::Generic_GenericData<T> > alceptr = std::make_shared< pg::Generic_GenericData<T> >(t);
    pg::Dataptr alce = std::static_pointer_cast<pg::Data>(alceptr);
    return alce;
    //return pg::Dataptr(new pg::Generic_GenericData<T> (t));
},  std::enable_if_t<std::is_base_of<T, pg::Data>::value> =0
*/
template <class T>
pg::Dataptr getData(T& t){
    return  _getData_primitive(t, std::is_fundamental<T>());
}

}
