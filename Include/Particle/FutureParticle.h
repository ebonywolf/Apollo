#pragma once

#include "Data/DataTuple.h"
#include "DataType/GenericDatatype.h"
#include "MetaTools/GetType.h"
#include "Particle_Base.h"
#include <sstream>
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
        Debug("before check:", future.ready());

        context->update();
        Debug("After check:", future.ready());
        return future.getData();
    }
    virtual std::string toString() const
    {
        std::stringstream os;
        if (future.ready())
            os << "Future:" << getType()->toString() << " value:"
                    << future.getData() << std::endl;
        else
            os << "Future:" << getType()->toString()
                    << " Not ready, waiting on " << getContext()
                    << std::endl;
        return os.str();
    }
    friend std::ostream& operator<<(std::ostream& os, const FutureParticle& data ){
        if(data.future.ready())
            os<<"Future:"<<data.getType()->toString()<<" value:"<<data.future.getData()<<std::endl;
        else
            os<<"Future:"<<data.getType()->toString()<<" Not ready, waiting on "<<data.getContext()<<std::endl;
        return os;
    }

};




}



