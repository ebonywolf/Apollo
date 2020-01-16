
#include "EurusSet.h"
#include "Packet.h"
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
    for(auto x: _internal) {
       if(x.second.contains(d))
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
    _internal[ptr->getDataPair()].extend(ptr);
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
    auto channel = d.getChannel()->getInverseDataPair();

    for(auto x: _internal) {
       bool contains = x.second.contains(channel);
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
    return _key->toString();
}
Datatypeptr EurusSet::junction(Datatypeptr other) const {
    throw "todo";
}

Datatypeptr EurusSet::getFrom() const{
    throw "todo";
}
Datatypeptr EurusSet::getTo() const{

    throw "todo";
}
Datatypeptr EurusSet::getInverseDataPair() const{
    throw "todo";
}
Datatypeptr EurusSet::getDataPair() const{
    return std::make_shared<DataPair>(getFrom(),getTo());
}







}
