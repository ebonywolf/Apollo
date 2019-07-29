#pragma once


#include "Entity.h"


template<class Data>
struct EntityArray : public Entity<Data>{

    EntityList(){
        updateFunc = Node::doShit;
    }
    static void doShit(Entityptr ent){
        auto node = std::static_pointer_cast<Node>(ent);
    }

};
