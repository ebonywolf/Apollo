#include "OmniSet.h"
#include "Packet.h"
namespace pg
{

/*
std::size_t EntityptrHash::operator()(const pg::Processptr& k) const
{
    return std::hash<KeyHash>()(k->getHashKey());
}*/
OmniSet::OmniSet(){
   _key= std::make_shared<KeySet>();
}

Dataptr OmniSet::handle(Entityptr ent, Dataptr d) const
{
    throw "todo";
    for(auto x: _internal) {
        x.second->handle( ent,  d);
    }
}
int OmniSet::size()const
{
    return _internal.size();
}


void OmniSet::omniUpdate(const Processptr context)
{
    for(auto x: _internal) {
        x.second->omniUpdate(context);
    }
}
void OmniSet::eurusUpdate(const Processptr context)
{
    for(auto x: _internal) {
        x.second->eurusUpdate(context);
    }
}
void OmniSet::warnEurusChange(Processptr context)
{
    for(auto x: _internal) {
        x.second->warnEurusChange(context);
    }
}


Datatypeptr OmniSet::getHashKey()const
{
   return _key;
};


Future OmniSet::send(Dataptr sentData, const Datatypeptr fromType, Processptr context )
{
    throw "todo";
    for(auto x: _internal) {
        x.second->send(sentData,fromType,context  );
    }
}

void OmniSet::warnOmniChange(Processptr context)
{
    for(auto x: _internal) {
        x.second->warnOmniChange(context);
    }
}

Processptr OmniSet::getOmni(Datatypeptr name) const
{
    return _internal.at(name);
}

Processptr OmniSet::getBase()const
{
    return std::make_shared<OmniSet>();
}

void OmniSet::extend(Processptr ptr)
{
    if( ptr->isNull() ) {
        return;
    }
    auto h= ptr->getHashKey();
    _internal.insert({ h, ptr });
    _key->join(h);
}

bool OmniSet::hasOmni(Datatypeptr name) const
{
    return _internal.count(name);
}

Processptr OmniSet::getEurus() const
{
    Processptr omniSet = std::make_shared<OmniSet>();
    for(auto x: _internal) {
        omniSet->extend( x.second->getEurus());
    }
    return omniSet;
}
Processptr OmniSet::getOmni() const
{
    Processptr omniSet = std::make_shared<OmniSet>();
    for(auto x: _internal) {
        omniSet->extend( x.second->getOmni());
    }
    return omniSet;
}

bool OmniSet::hasEurus(Datatypeptr p) const
{
    std::cout<<"Omni:"<<*this<<_internal.size()<<std::endl;
    for(auto x: _internal) {
        if( x.second->hasEurus(p))
            return true;
    }
    return false;
}

bool OmniSet::contains(Datatypeptr d)const
{
    return d->contains(d);
}

void OmniSet::receiveData(Processptr context, Packet packet)
{
    for(auto x: _internal) {
        x.second->receiveData(context,packet);
    }
}


void OmniSet::join( Datatypeptr other) {
throw "todo";
}

std::string OmniSet::toString() const{
    return _key->toString();
}
Datatypeptr OmniSet::junction(Datatypeptr other) const {
    throw "todo";
}


Datatypeptr OmniSet::getFrom() const{
    throw "todo";
}
Datatypeptr OmniSet::getTo() const{
    throw "todo";
}
Datatypeptr OmniSet::getInverseDataPair() const{
    throw "todo";
}
Datatypeptr OmniSet::getDataPair() const{
    throw "todo";
}




}
