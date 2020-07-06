#pragma once

#include <Entity/Entity.h>

namespace pg{

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

}
