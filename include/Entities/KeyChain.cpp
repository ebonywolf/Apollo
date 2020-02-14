#include "KeyChain.h"
#include <iostream>
using namespace std;

namespace pg{



std::string  KeyChain::toString() const{
    string s="";
    bool first=true;
    for (auto& x: _internal) {
        if(!first)
            s+="_";
        else
            first = false;

        s+=x->toString();
    }
    return s;
}



void KeyChain::join( Datatypeptr other){
   // throw "todo";

    std::shared_ptr<const KeyChain> alce = std::dynamic_pointer_cast<const KeyChain>(other);
    if(alce){
        _internal.insert(_internal.end() ,alce->_internal.begin(),alce->_internal.end());
    }else{
        _internal.push_back( other->getHashKey());
     //   _internal[  other->getHashKey()->toString()]=other;
    }

}
bool KeyChain::contains(Datatypeptr d) const
{
  throw "todo";
}
Datatypeptr KeyChain::junction(Datatypeptr other) const {
    auto copy = std::make_shared<KeyChain>(*this);
    copy->join(other);
    return copy;
}
Datatypeptr KeyChain::getHashKey() const{
    return shared_from_this();
}
Datatypeptr KeyChain::getFrom() const{
    throw "todo";
}
Datatypeptr KeyChain::getTo() const{
    throw "todo";
}
Datatypeptr KeyChain::getInverseDataPair() const{
    throw "todo";
}
Datatypeptr KeyChain::getDataPair() const{
    throw "todo";
}


}
