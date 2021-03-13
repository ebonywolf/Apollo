
#ifndef INCLUDE_PARTICLE_UNCHARGEDPARTICLE_H_
#define INCLUDE_PARTICLE_UNCHARGEDPARTICLE_H_
#pragma once


#include "Particle_Base.h"
namespace ap{
class UnchargedParticle : public Particle_Base{
public:
    pg::Entityptr ent;

    UnchargedParticle(pg::Entityptr ent):ent(ent){}
    ~UnchargedParticle(){

    }

    virtual pg::Entityptr getContext()const{
        return ent;
    }
    virtual pg::Datatypeptr getType() const{
        return ent->getDataPair();
    }
    virtual pg::Dataptr getValue() const {
        ent->getEurus();
    }
};



}

#endif /* INCLUDE_PARTICLE_UNCHARGEDPARTICLE_H_ */
