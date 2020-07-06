#pragma once
#include <Entity/Entity.h>

namespace pg{

template<typename T, T> struct Dummy { };

class UniqueEntity;

#define TO_STR(X) #X
template <class T>
class GenericEntity: public Entity
{
public:
    using Myptr = std::shared_ptr<T>;
    GenericEntity() : GenericEntity( typeid(T).name())
    {
    }
    GenericEntity(std::string name) :
        _key( std::make_shared<HashKey>(name))
   {
   }

    template <class ...D>
    GenericEntity(std::string name, D... t ) : Entity(t...),
    _key( std::make_shared<HashKey>(name))
    {
    }

    virtual ~GenericEntity(){}

    Processptr getBase() const override{
        return std::make_shared<UniqueEntity>(toString());
    }

    virtual std::string toString() const{
        return _key->toString();
    }


    Datatypeptr getHashKey() const
    {
        return _key;
    }
    static PlaceHolder _instance;

    typedef Dummy<PlaceHolder&, _instance> __dummmy;
    GenericEntity(PlaceHolder)
    {
    }
private:
    Datatypeptr _key;

} ;
template <class T>
Entity::PlaceHolder GenericEntity<T>::_instance = Entity::createGlobalEntity<T>();




}
