
#include "EntitySet.h"
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

int EurusSet::size()const
{
    return _internal.size();
}
Datatypeptr EurusSet::getHashKey()const
{
    throw "todo";
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
void EurusSet::warnEurusChange(Processptr context)
{
    for(auto x: _internal) {
        x.second.warnEurusChange(context);
    }
}
void EurusSet::warnOmniChange(Processptr context)
{
    for(auto x: _internal) {
        x.second.warnOmniChange(context);
    }
}

Processptr EurusSet::getNull()const
{
    return std::make_shared<EurusSet>();
}

void EurusSet::extend(Processptr ptr)
{
    _internal[ptr->getDataPair()].extend(ptr);
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

Dataptr EurusSet::handle(Entityptr ent, Dataptr d) const{
    throw "todo";
}

Future EurusSet::send(Dataptr sentData, const Datatypeptr fromType, Processptr context ){
throw "todo";
}


Processptr EurusSet::getOmni(Datatypeptr name) const {
    throw "todo";
}


bool EurusSet::hasEurus(Datatypeptr p) const
{
    for(auto x: _internal) {
        if( x.second.hasEurus(p))
            return true;
    }
    return false;
}
void EurusSet::receiveData(Processptr context, Packet packet)
{

    for(auto x: _internal) {
        x.second.receiveData(context,packet);
    }
}

}
