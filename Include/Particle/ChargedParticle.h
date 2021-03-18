#pragma once

#include "Apollo.h"
#include <sstream>
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
    std::string toString() const{
        std::stringstream ss;
        ss<<"Context:"<<context->toString()<<
                "\nCharge:"<<charge->toString()<<"n\Type:"<<type->toString();
        return ss.str();
    }
    virtual ~ChargedParticle(){}

};

}

