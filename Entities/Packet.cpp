#include "Packet.h"

#include "Entity.h"

namespace pg{

void PacketMap::push(Entityptr context,Packet p){
    _base[context->getName()].push_back(p);
}


PacketList PacketMap::pull(Entityptr context){
    auto alce = _base[context->getName()];
    _base.erase(context->getName());
    return alce;
}

int PacketMap::getSize(Entityptr context) const{
    std::string name = context->getName();
    if(_base.count(name)){
        return _base.at(name).size();
    }else
        return 0;
}






}
