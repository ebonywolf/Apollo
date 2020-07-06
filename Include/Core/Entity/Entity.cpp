#include "Entity/Entity.h"
#include "Entity/UniqueEntity.h"

namespace pg
{


void Entity::addEurus(const Processptr obj)
{
  //  std::cout<<"Adding:"<<obj->toString()<<std::endl;
    //if(_eurus.count(obj))throw "repeat

     _eurus->extend(obj);
 }
std::ostream& operator<<(std::ostream& os, const Processptr data){
        os << data->toString();
        return os;
    }


Entityptr Entity::getGlobal()
{
    static Entityptr global;
    if(!global) {
        global = std::make_shared<UniqueEntity>("_Global");
    }
    return global;
}

void Entity::handle(Entityptr ent, Packet d)
{
     Entityptr me = std::static_pointer_cast<Entity_Base>(this->shared_from_this());
    _eurus->handle(me , d);
}

Future Entity::send(Dataptr sentData,const Datatypeptr fromType, Processptr context)
{
    const auto toType = sentData->getType();
    Datatypeptr pair = std::make_shared<DataPair>(fromType, toType);

    auto reversePair = pair->getInverseDataPair();

    bool sent = false;
    Future future(fromType);
    if( !_omni->hasEurus( reversePair) ){
        throw std::runtime_error(std::string("no handler for: ") + reversePair->toString());
    }
    Packet packet( sentData, future, context);

    _sentBuffer.push(context,packet);
    context->warnOmniChange(this->shared_from_this());

    return future;
}


void Entity::warnOmniChange(const Processptr context)
{
    _senders->extend(context);
}


Datatypeptr Entity::junction( Datatypeptr other)  const
{

    throw "Todo";
}
Datatypeptr  Entity::getFrom()  const
{

    throw "Todo";
}
Datatypeptr  Entity::getTo() const
{

    throw "Todo";
}
Datatypeptr  Entity::getInverseDataPair() const
{

    throw "Todo";
}
Datatypeptr  Entity::getDataPair() const
{
    return _eurus;
}



}
