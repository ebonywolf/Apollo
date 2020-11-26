#ifndef INCLUDE_PARTICLE_JSONPARTICLE_H_
#define INCLUDE_PARTICLE_JSONPARTICLE_H_

#include "SpecialEntities/JsonEntity.h"

#include "ChargedParticle.h"
#include <fstream>
#include <string>

namespace ap{

class ChargedParticle;

class JsonParticle : public ap::ChargedParticle
{
public:
    JsonParticle(std::string name);
private:
    pg::Entityptr readFromFile(std::string file);

};

}
#endif /* INCLUDE_PARTICLE_JSONPARTICLE_H_ */
