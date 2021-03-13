#pragma once

#include "Apollo.h"

namespace ap {

class ChargedParticle: public Particle_Base {
    pg::Entityptr context;
    pg::Dataptr charge;
    pg::Datatypeptr type;
    ChargedParticle() = delete;
public:
    ChargedParticle(pg::Entityptr context, pg::Dataptr input, pg::Datatypeptr output)
    :context(context),charge(input), type(output)
    {
        this->context = context;
    }
    pg::Entityptr getContext()const override{
        return context;
    }

    pg::Datatypeptr getType() const{
        return type;
    }
    virtual pg::Dataptr getValue() const{
        return charge;
    }

    virtual ~ChargedParticle(){}

};

}

