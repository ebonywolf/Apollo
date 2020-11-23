#ifndef INCLUDE_PARTICLE_JSONPARTICLE_H_
#define INCLUDE_PARTICLE_JSONPARTICLE_H_

#include "SpecialEntities/JsonEntity.h"
#include "Particle.h"
#include "ChargedParticle.h"
#include <fstream>
#include <string>

namespace ap{

class JsonParticle: public Particle_Base {
public:
    JsonParticle(std::string name){
        readFromFile(name);
    }

    void readFromFile(std::string file);
    virtual pg::Entityptr getEntity() {}
    virtual Particle send(Particle p){}

};

}
#endif /* INCLUDE_PARTICLE_JSONPARTICLE_H_ */
