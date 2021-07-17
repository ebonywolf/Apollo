#pragma once

#include "Identification/KeyChain.h"
#include "MetaTools/GetType.h"
#include "MetaTools/KeyFab.h"

namespace pg{



template <class ...T>
struct DataTuple : public std::tuple<Tools::base_type<T>...>, public Data{

    DataTuple():
        _key(_createKey())
    {
    }
    DataTuple(T...t): std::tuple<Tools::base_type<T>...>(t...),
           _key(_createKey_params(t...))
    {
    }
    virtual std::string toString() const{
       return _key->toString();
    }

    virtual Datatypeptr getType() const{
        return _key;
    }
private:
    Datatypeptr _createKey()
    {
        auto alceKey =std::make_shared<KeyChain>();
        createKey_base<T...>(alceKey);
        return alceKey;
    }
    template <typename ...D>
    Datatypeptr _createKey_params(D&...t)
    {
	   auto alceKey =std::make_shared<KeyChain>();
	   createKey_base_params<D...>(alceKey, t...);
	   return alceKey;
    }
    Datatypeptr _key;
};





}
