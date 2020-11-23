
#ifndef INCLUDE_PARTICLE_CHARGEDPARTICLE_H_
#define INCLUDE_PARTICLE_CHARGEDPARTICLE_H_
#include "Apollo.h"

namespace ap {

class ChargedParticle: public Particle_Base {
    pg::Entityptr data;
    ChargedParticle() = delete;
public:
    ChargedParticle(pg::Entityptr ptr)
    {
        this->data = ptr;
    }
    virtual ~ChargedParticle(){}

    virtual pg::Entityptr getEntity();
    virtual Particle send(Particle p);
};

}

#endif /* INCLUDE_PARTICLE_CHARGEDPARTICLE_H_ */
