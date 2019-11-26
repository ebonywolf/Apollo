#include "Entity.h"
#include "SpecialEntities.h"

namespace pg {


void Entity::addEurus(const Processptr obj){
    //if(_eurus.count(obj))throw "repeat
    _eurus->extend(obj);
}


Entityptr Entity::getGlobal(){
    static Entityptr global;
    if(!global){
        global = std::make_shared<UniqueEntity>("_Global");
        // Entityptr(new Entity());
        // global->["GLOBAL"] = global;//shared ptr pointing to itself,
    }
    return global;
}

Dataptr Entity::handle( Entityptr ent, Dataptr d) const {
    /*
    if(processes.count(p.getChannel())){
        auto func = getProcess().get(p.getChannel());
        Dataptr answer = func->handle(this->shared_from_this(),p.data);
        p.futureAnswer.set(answer);

    }
    else{
        if(_eurus.count(p.getChannel())){
            auto alce = _eurus[p.getChannel()];
            alce->handle(p);
        }
        else{
            throw "foo";
        }
    }
    */
}

Future Entity::send(Dataptr sentData,const Datatypeptr fromType, Processptr context){
    const auto toType = sentData->getType();
    Datatypeptr pair = std::make_shared<DataPair>(fromType, toType);
    auto reversePair = pair->getInverseDataPair();

    bool sent = false;
    Future future(fromType);

    throw "Todo";
    /*
    for(auto& to : _omni){

        if(to->hasEurus(reversePair)){
            sent = true;
        }
        Packet packet(to, sentData, future, context);
        _sentBuffer.push(context, packet);
        context->warnOmniChange(this->shared_from_this());
    }
    */
    if(!sent){
        throw std::runtime_error(std::string("no handler for: ") + reversePair->getHashKey()->toString());
    }
    return future;
}

}
