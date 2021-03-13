#pragma once
#include "Entity/UniqueEntity.h"
#include <json/json.h>
namespace pg{

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

                    std::cout<<"Editing:"<<current->toString()<<"-"<<current->getEurus()->toString()<<std::endl;
                    current->extend(toadd);
                    global->addEurus(current);
                    addEurus(current);
                    addOmni(current);
                }else{
                    std::cout<<"Creating:"<<toadd->toString()<<std::endl;

                    global->addOmni(toadd);
                    global->addEurus(toadd);
                    addEurus(toadd);
                    addOmni(toadd);
                }

            } else {
                //  throw "foo";
            }
        }
    }
};

struct ContextCreator {
    static std::shared_ptr<pg::Entity> createFromJson(std::string file)
    {
        std::ifstream in(file);
        if(!in.is_open()) {
            throw "unable to open file";
        }
        Json::Value val;

        in>>val;
        std::shared_ptr<pg::Entity> novo = std::shared_ptr<pg::Entity>(new JsonEntity(file,val));

        return novo;
    }

};

}
