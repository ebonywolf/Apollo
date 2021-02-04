#pragma once

#include "Core/Base.h"
#include "Entity/Entity.h"

namespace ap{
class Particle_Base;
class Particle;
class Particle_Base: public enable_shared_from_this_virtual<Particle_Base>, public pg::Data{
public:

    virtual pg::Datatypeptr getType() const=0;
    virtual pg::Processptr getContext()const =0;
 //   virtual Particle interact(Particle other)const=0;



};

}
