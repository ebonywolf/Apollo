#pragma once
#include <memory>

namespace pg{
    class Data;
    using Dataptr = std::shared_ptr<Data>;

    template <class T>
    struct GenericData;

    template <class T>
    struct Generic_GenericData;
}



template <class T, class D>
auto _cast(D* d){
    return static_cast<T*>(d);
}

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
auto _deRef(T& t){
    auto alce = std::static_pointer_cast<T>(t);
    return *alce.get();
}

template <class T>
auto _deRef(T* t){
    return std::make_shared<T>(t);
}




