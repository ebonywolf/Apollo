#pragma once

#include "Data/DataTuple.h"
#include "DataType/GenericDatatype.h"
#include "MetaTools/GetType.h"
#include "Particle_Base.h"

namespace ap{


class FutureParticle : public Particle_Base {
public:

    pg::Entityptr context;
    pg::Future future;
    FutureParticle(pg::Entityptr context,pg::Future future):context(context), future(future){

    }
    virtual pg::Entityptr getContext()const {
        return context;
    }
    virtual pg::Datatypeptr getType() const{
        return future->getType();
    }

    virtual pg::Dataptr getValue() const {
        std::cout <<"before check"<< future.ready() <<std::endl;

        context->update();
        std::cout << "after check"<<future.ready() <<std::endl;

        return future.getData();
    }
};




}



