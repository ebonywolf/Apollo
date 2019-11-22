#pragma once
#include "Entity.h"

namespace pg{

template<typename T, T> struct Dummy { };


#define TO_STR(X) #X
template <class T>
class GenericEntity: public Entity
{
public:
    using Myptr = std::shared_ptr<T>;
    GenericEntity() :_name( typeid(T).name())
    {
    }
    GenericEntity(std::string name) :_name(name)
   {
   }

/*Todo Make this work
    template <class ...D>
    GenericEntity(std::string name, D... t ) : Entity(t...), _name(name)
    {
    };
    */
    virtual ~GenericEntity(){}


    std::string getHashKey() const
    {
        return _name;
    }
    static PlaceHolder _instance;

    typedef Dummy<PlaceHolder&, _instance> __dummmy;
    GenericEntity(PlaceHolder)
    {
    }
private:
    std::string _name;

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


                if( global->hasOmni(name) ) {
                    auto current = global->getOmni(name);
                    auto c_current=  cast(current);

                    c_current->extend(toadd);
                    global->addEurus(current);
                    addEurus(current);


                }else{
                    global->addOmni(toadd);
                    global->addEurus(toadd);
                    addEurus(toadd);
                }

            } else {
                //  throw "foo";
            }

        }
    }
    virtual std::string getHashKey() const
    {
        return _name;
    }
    std::string _name;
};



class UniqueEntity :public Entity{
public:
    UniqueEntity(std::string name):_name(name){
    }
    std::string getHashKey() const
    {
        return _name;
    }
private:
    std::string _name;
    static int _cont;


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
