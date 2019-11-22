#include "Packet.h"

#include "Entity.h"

namespace pg{

void PacketMap::push(Processptr context,Packet p){
    _base[context->getHashKey()].push_back(p);
}


PacketList PacketMap::pull(Processptr context){
    auto alce = _base[context->getHashKey()];
    _base.erase(context->getHashKey());
    return alce;
}

int PacketMap::getSize(Processptr context) const{
    std::string name = context->getHashKey();
    if(_base.count(name)){
        return _base.at(name).size();
    }else
        return 0;
}






}
