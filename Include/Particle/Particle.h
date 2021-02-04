
#pragma once

#include "DataType/DataTuple.h"
#include "DataType/GenericDatatype.h"
#include "MetaTools/GetType.h"
#include "Particle_Base.h"
namespace ap{

class FutureParticle : public Particle_Base {
public:

    pg::Processptr context;
    pg::Future future;
    FutureParticle(pg::Processptr context,pg::Future future):context(context), future(future){

    }
    virtual pg::Processptr getContext()const {
        return context;
    }
    virtual pg::Datatypeptr getType() const{
        return future->getType();
    }
};

class Particle : public std::shared_ptr<Particle_Base>{
public:
    template <class T>
    Particle(T* t):std::shared_ptr<Particle_Base>(t)
    {
    }

    Particle run() const;

    Particle send(pg::Dataptr inputData, pg::Dataptr output, pg::Entityptr context) const {
        pg::Processptr me = get()->getContext();

        pg::Future answ  = me->send(inputData, output->getType(), context);
        return Particle( new FutureParticle(context, answ));
    }
    Particle interact(Particle other) const{

    }



    template<class ...OUTPUT, class ...INPUT>
    Particle send(INPUT... input) const {
        pg::Entityptr me = get()->getContext();

        pg::Future answ  = me->send<OUTPUT...>(input...);
        return Particle(new FutureParticle(me,answ));
//       send(in)
//
//       pg::Entityptr me = get()->getContext();
//       pg::Future answ = send(inputData, output.getType(), me);
//       outputParticle(answ);
    }


};

template <class T>
Particle makeParticle(T* t){
    Particle newParticle = Particle(t);
    return newParticle;
}




}

