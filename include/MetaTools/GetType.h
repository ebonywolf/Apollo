#pragma once

#include "Entities/GenericData.h"

namespace Tools{



template <class T>
pg::Datatypeptr _getType_normal(T& t, std::true_type){
    return t.getType();
}

template <class T>
pg::Datatypeptr _getType_normal(T& t,std::false_type){
    pg::Generic_GenericData<T> genericData(t);
    return genericData.getType();
}
/*
template <class T>
pg::Datatypeptr _getType_ptr(std::shared_ptr<T> t, std::true_type){
    return t.getType();
}

template <class T>
pg::Datatypeptr _getType_ptr(std::shared_ptr<T> t,std::false_type){
    pg::GenericData<T> genericData;
    return genericData.getType();
}*/


template <class T>
pg::Datatypeptr getType(T& t){
    return _getType_normal(t, std::is_base_of<pg::Data,T>() );
}

template <class T>
pg::Datatypeptr getType(std::shared_ptr<T> t){
    T alce;
    return _getType_normal(alce, std::is_base_of<pg::Data,T>());
}



}


