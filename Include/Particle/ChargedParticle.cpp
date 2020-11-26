#include "ChargedParticle.h"

#include "NullParticle.h"
#include "ChargedParticle.h"
#include "JsonParticle.h"

namespace ap {




Particle ChargedParticle::send(Particle p)
{
    p->getEntity();
    data->send(p->getEntity());
    throw "todo";
}



pg::Entityptr ChargedParticle::getEntity()
 {
     return data;
 }




}
