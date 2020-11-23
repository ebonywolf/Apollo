#include "Particle.h"
#include "NullParticle.h"

namespace ap {

void Particle::run()
{
    send(NullParticle());
}



}
