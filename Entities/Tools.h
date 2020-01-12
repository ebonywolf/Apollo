#pragma once
#include <memory>
namespace pg{
    class Data;
}

template <class T>
auto _getType(std::shared_ptr<T> t){
    T alce;
    return alce.getType();
}
template <class T>
auto _getType(T t){
    return t.getType();
}


template <class T>
auto _getObj(std::shared_ptr<T> t){
    return std::static_pointer_cast<pg::Data>(t);
}
template <class T>
auto _getObj(T t){
    return std::make_shared<T>(t);
}



/*
template <class T, class D>
auto _cast(D* d){
    return static_cast<T*>(d);
}
*/
//Dynamic casts B and adds it to object a

template <class T,class U>
void _castPtr(T& a, std::shared_ptr<U> b){

    T* alceptr= static_cast<T*>(  b.get() );
    a = *alceptr;
}

template<class T,class U>
void _castPtr(std::shared_ptr<T>& a, std::shared_ptr<U> b){
    a = std::dynamic_pointer_cast<T>(b);
    if(!a){
        throw "foo";
    }

}


template <class T>
auto _deRef(T t){
    auto alce = std::static_pointer_cast<T>(t);
    return *alce.get();
}

template <class T>
auto _deRef(T* t){
    return std::make_shared<T>(t);
}




