
#ifndef INCLUDE_PARTICLE_NULLPARTICLE_H_
#define INCLUDE_PARTICLE_NULLPARTICLE_H_

#include "Particle.h"



namespace ap{

class NullParticle : public Particle {
    virtual pg::Entityptr getEntity() {
        return 0;
    }
    virtual Particle send(Particle p){
        return 0;
    }
};

}

#endif /* INCLUDE_PARTICLE_NULLPARTICLE_H_ */
