#include "ChargedParticle.h"

#include "NullParticle.h"
#include "ChargedParticle.h"
#include "JsonParticle.h"

namespace ap {




pg::Entityptr ChargedParticle::getEntity()
{
    return data;
}
Particle send(Particle p)
{
    throw "todo";
}

/*

 Particle ChargedParticle::getEntity(std::string name)
 {
 auto key = std::make_shared<pg::HashKey>(name);

 if (this->get()->hasOmni(key)) {
 auto current = this->get()->getOmni(key);
 return ChargedParticle(current);
 } else {
 return NullParticle();
 }

 }
 */

}
