#include "Particle.h"

#include "UnchargedParticle.h"
#include "ChargedParticle.h"
#include "Apollo.h"
namespace ap
{

Particle Particle::run() const {
      auto me = get()->getContext();
      pg::Entity::getGlobal();
      pg::Dataptr input = pg::Null();
      pg::Datatypeptr output = pg::All();
      ap::ChargedParticle* alce = new ap::ChargedParticle(me,input,output );
      Particle letTherebeLight = Particle(alce) ;
      Particle result = interact(letTherebeLight);
      return result;
 }

Particle makeParticle(pg::Entityptr ptr){
    ap::UnchargedParticle* alce = new ap::UnchargedParticle(ptr);
    Particle newParticle = Particle(alce);
    return newParticle;
}



}
