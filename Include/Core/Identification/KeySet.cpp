#include "KeySet.h"
using namespace std;

namespace pg{

Datatypeptr HashKey::junction(Datatypeptr other) const {
    auto kset = make_shared<KeySet>();
    kset->join( this->shared_from_this() );
    kset->join( other );
    return kset;
}
bool HashKey::contains(Datatypeptr d)const
{
     return value==d->toString();
}
Datatypeptr HashKey::getHashKey() const{
    return this->shared_from_this();
}
Datatypeptr HashKey::getFrom() const{
    throw "todo";
}
Datatypeptr HashKey::getTo() const{
    throw "todo";
}
Datatypeptr HashKey::getInverseDataPair() const{
    throw "todo";
}
Datatypeptr HashKey::getDataPair() const{
    throw "todo";
}


std::string  KeySet::toString() const{
    string s="";
    bool first=true;
    for (auto& x: _internal) {
        if(!first)
            s+=".";
        else
            first = false;

        s+=x.first;
    }
    return s;
}


void KeySet::join( Datatypeptr other){
    std::shared_ptr<const KeySet> alce = std::dynamic_pointer_cast<const KeySet>(other);
    if(alce){
        _internal.insert(alce->_internal.begin(),alce->_internal.end());
    }else{
        _internal[  other->getHashKey()->toString()]=other;
    }
}
bool KeySet::contains(Datatypeptr d)const
{
    return _internal.count(d->toString());
}
Datatypeptr KeySet::junction(Datatypeptr other) const {
    throw "todo";
}
Datatypeptr KeySet::getHashKey() const{
    throw "todo";
}
Datatypeptr KeySet::getFrom() const{
    throw "todo";
}
Datatypeptr KeySet::getTo() const{
    throw "todo";
}
Datatypeptr KeySet::getInverseDataPair() const{
    throw "todo";
}
Datatypeptr KeySet::getDataPair() const{
    throw "todo";
}


}
