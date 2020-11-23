#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include "Core/Base.h"
#include "Entity/Entity.h"

namespace ap{



class Particle_Base;
using Particle = std::shared_ptr<Particle_Base>;

class Particle_Base: public enable_shared_from_this_virtual<Particle_Base>{
public:
    virtual pg::Entityptr getEntity() = 0;
    virtual Particle send(Particle p)=0;
};

using Particle = std::shared_ptr<Particle_Base>;



}

#endif //PARTICLE_H
