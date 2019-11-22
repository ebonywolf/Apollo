#include "Entity.h"
#include "SpecialEntities.h"

namespace pg {

std::size_t EntityptrHash::operator()(const pg::Entityptr& k) const {
    return std::hash<std::string>()(k->getHashKey());
}

bool Entitycmp::operator()(const Entityptr& t1, const Entityptr& t2) const {
    return t1->getHashKey() == t2->getHashKey();
}

void Entity::addEurus(const Processptr obj){
    //if(_eurus.count(obj))throw "repeat
    _eurus.insert(obj);
}

bool EntitySet::contains(std::string name) const {
    Entityptr alce = std::make_shared<UniqueEntity>(name);
    return count(alce);
}
Entityptr EntitySet::get(std::string name) const {
    Entityptr alce = std::make_shared<UniqueEntity>(name);
    auto it = find(alce);
    return *it;
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

Future Entity::send(Dataptr sentData, const Datatype fromType, Processptr context){
    const auto toType = sentData->getType();
    DataPair pair(fromType, toType);
    DataPair reversePair = pair.getInverse();

    bool sent = false;
    Future future(fromType);

    for(auto& to : _omni){

        if(to->hasEurus(reversePair)){
            sent = true;
        }
        Packet packet(to, sentData, future, context);
        _sentBuffer.push(context, packet);
        context->warnOmniChange(this->shared_from_this());
    }
    if(!sent){
        throw std::runtime_error(std::string("no handler for: ") + reversePair.getHashKey());
    }
    return future;
}

}
