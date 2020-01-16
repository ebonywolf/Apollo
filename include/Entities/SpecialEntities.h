#pragma once
#include "Entity.h"

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
//std::make_shared<GenericEntity<T>>(PlaceHolder());




class UniqueEntity :public Entity{
public:
    UniqueEntity(std::string name){
        _key = std::make_shared<HashKey>(name);
    }
    Datatypeptr getHashKey() const
    {
        return _key;
    }
    Processptr getBase() const{
        return std::make_shared<UniqueEntity>("null");
    }
    std::string toString() const{
        return _key->toString();
    }

private:
    Datatypeptr _key;
};



class JsonEntity : public UniqueEntity
{
public:
    JsonEntity(std::string _name):UniqueEntity(_name)
    {

    }

    JsonEntity(std::string _name,Json::Value val):UniqueEntity(_name)
    {
        for(auto& name: val.getMemberNames()) {
            Json::Value& subval = val[name];
            if(subval.isObject()) {
                Entityptr toadd = Entityptr(new JsonEntity(name, subval));

                auto global = getGlobal();
                auto key = std::make_shared<HashKey>(name);

                if( global->hasOmni(key) ) {
                    auto current = global->getOmni(key);

                    std::cout<<"Editing:"<<current->toString()<<std::endl;
                   // auto c_current=  cast(current);
                   // c_current->extend(toadd);

                    current->extend(toadd);
                    global->addEurus(current);
                    addEurus(current);
                }else{
                    std::cout<<"Creating:"<<toadd->toString()<<std::endl;

                    global->addOmni(toadd);
                    global->addEurus(toadd);
                    addEurus(toadd);
                }

            } else {
                //  throw "foo";
            }
        }
    }
};




struct ContextCreator {
    static Particle createFromJson(std::string file)
    {
        std::ifstream in(file);
        if(!in.is_open()) {
            throw "unable to open file";
        }
        Json::Value val;

        in>>val;
        Particle novo = Particle(new JsonEntity(file,val));

        return novo;
    }

};



}
