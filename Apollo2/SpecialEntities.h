#pragma once
#include "Entity.h"

namespace pg{



#define TO_STR(X) #X
template <class T>
class GenericEntity: public Entity
{
public:
    template <class ...D>
    GenericEntity(std::string name, D... t ) : Entity(t...), name(name)
    {
    };


    std::string getName() const
    {
        return name;
    }
    static PlaceHolder _instance;
    static_assert(&_instance);
    GenericEntity(PlaceHolder)
    {

    }
protected:
    std::string name;

} ;

template <class T>
Entity::PlaceHolder GenericEntity<T>::_instance = Entity::createGlobalEntity<T>();
//std::make_shared<GenericEntity<T>>(PlaceHolder());


class JsonEntity : public Entity
{
public:
    JsonEntity(std::string _name,Json::Value val):_name(_name)
    {
        for(auto& name: val.getMemberNames()) {
            Json::Value& subval = val[name];
            if(subval.isObject()) {

                Entityptr toadd = Entityptr(new JsonEntity(name, subval));

                auto global = getGlobal();

                std::cerr<<"Global Size:"<<global->_eurus.size()<<std::endl;
                if( global->hasOmni(name) ) {
                    std::cerr<<"Adding"<<name<<std::endl;
                    auto current = global->getOmni(name);
                    current->extend(toadd);
                    global->addEurus(current);

                    addEurus(current);
                }else{
                    std::cerr<<"Creating"<<name<<std::endl;
                    global->addOmni(name,toadd);
                    global->addEurus(toadd);
                    addEurus(toadd);
                }
            } else {
                //  throw "foo";
            }

        }

    }
    virtual std::string getName() const
    {
        return _name;
    }
    std::string _name;
};


struct ContextCreator {

    static Entityptr createFromJson(std::string file)
    {
        std::ifstream in(file);
        if(!in.is_open()) {
            throw "unable to open file";
        }
        Json::Value val;

        in>>val;
        Entityptr novo = Entityptr(new JsonEntity(file,val));

        return novo;
    }

};



}
