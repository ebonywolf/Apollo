#pragma once

#include "Apollo.h"

namespace ap {

class ChargedParticle: public Particle_Base {
    pg::Processptr context;
    pg::Dataptr charge;
    ChargedParticle() = delete;
public:
    ChargedParticle(pg::Processptr context, pg::Dataptr input, pg::Datatypeptr output)
    {
        this->context = context;
    }
    pg::Processptr getContext()const override{
        return context;
    }

    pg::Datatypeptr getType() const{
        return charge->getType();
    }

    virtual ~ChargedParticle(){}

};

}

