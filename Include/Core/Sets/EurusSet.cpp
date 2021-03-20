
#include "EurusSet.h"
#include "Communication/Packet.h"
namespace pg
{

/*
std::size_t EntityptrHash::operator()(const pg::Processptr& k) const {
    return std::hash<std::string>()(k->getHashKey());
}

bool Entitycmp::operator()(const Processptr& t1, const Processptr& t2) const {
    return t1->getHashKey() == t2->getHashKey();
}
*/

EurusSet::EurusSet(){
   _key= std::make_shared<KeySet>();
}

int EurusSet::size()const
{
    return _internal.size();
}
Datatypeptr EurusSet::getHashKey()const
{
   return _key;
};

void EurusSet::omniUpdate(const Processptr context)
{
    for(auto x: _internal) {
        x.second.omniUpdate(context);
    }
}
void EurusSet::eurusUpdate(const Processptr context)
{
    for(auto x: _internal) {
        x.second.eurusUpdate(context);
    }
}
Processptr EurusSet::getEurus() const
{
    throw "todo";
   // return getDataPair();
}
void EurusSet::warnEurusChange(Processptr context)
{
    for(auto x: _internal) {
        x.second.warnEurusChange(context);
    }
}

bool EurusSet::contains(Datatypeptr d)const
{
    std::cout <<"Contains of:"<<this->toString() <<std::endl;
    for(auto x: _internal) {
        auto key = x.first;
        key->e_equals(d);
            return true;
    }
    return false;
}

void EurusSet::warnOmniChange(Processptr context)
{
    for(auto x: _internal) {
        x.second.warnOmniChange(context);
    }
}

Processptr EurusSet::getBase()const
{
    return std::make_shared<EurusSet>();
}

void EurusSet::extend(Processptr ptr)
{

    auto alce = ptr->getDataPair();

    std::cout <<"extend of:"<<this->toString() <<std::endl;
    std::cout <<"extend:"<<alce <<std::endl;
    if(alce->toString().size()==0){
        ptr->getDataPair();
    }
    _internal[alce].extend(ptr);
    _key->join(ptr->getDataPair());
}

bool EurusSet::hasOmni(Datatypeptr name) const
{
throw "todo";
}

Processptr EurusSet::getOmni() const
{
    throw "seriously";
    Processptr omni = std::make_shared<OmniSet>();
    for(auto x: _internal) {
        omni->extend( x.second.getOmni());
    }
    return omni;
}


void EurusSet::handle(Entityptr ent, Packet d)
{
    auto channel = d.getChannel()->getDataPair(); //We want the anti particle

    for(auto x: _internal) {
       auto& type = x.first;

       bool contains = channel->contains(type);

       if(contains ){
          x.second.handle(ent,d);
       }
    }
}

Future EurusSet::send(Dataptr sentData, const Datatypeptr fromType, Processptr context ){
throw "todo";
}


Processptr EurusSet::getOmni(Datatypeptr name) const {
    throw "todo";
}


bool EurusSet::hasEurus(Datatypeptr p) const
{
    return contains(p);

}
void EurusSet::receiveData(Processptr context, Packet packet)
{

    for(auto x: _internal) {
        x.second.receiveData(context,packet);
    }
}


std::string EurusSet::toString() const{
    if(size()==0){
        return "null";
    }
    return _key->toString();
}
Datatypeptr EurusSet::junction(Datatypeptr other) const {
    throw "todo";
}

Datatypeptr EurusSet::getFrom() const{
    throw  _key->getFrom();
}
Datatypeptr EurusSet::getTo() const{

    return _key->getTo();
}
Datatypeptr EurusSet::getInverseDataPair() const{
    throw std::make_shared<DataPair>(getTo(),getFrom());
}
Datatypeptr EurusSet::getDataPair() const{
    return std::make_shared<DataPair>(getFrom(),getTo());
}







}
