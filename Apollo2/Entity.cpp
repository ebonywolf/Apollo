#include "Entity.h"


namespace pg
{


std::size_t EntityptrHash::operator()(const pg::Entityptr& k) const
{
    return std::hash<std::string>()(k->getName());
}
void Entity::addEurus( const Entityptr obj)
{
    //if(_eurus.count(obj))throw "repeated handler";
    for(auto& proc: obj->getProcess()) {
        const Datatype from  = proc->getFrom();
        const Datatype to =  proc->getTo();
        auto& myset = _eurus(from,to);
        myset.insert(obj);
    }
}

bool EntitySet::contains(std::string name) const
{
    UniqueEntity alce(name);
    return count(alce);
}
Entityptr EntitySet::get(std::string name) const
{
     UniqueEntity alce(name);
     it = find(alce);
     return *it;
}



}
