
#pragma once

#include "DataType/DataTuple.h"
#include "DataType/GenericDatatype.h"
#include "MetaTools/GetType.h"
#include "Particle_Base.h"
#include <ostream>

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

class Particle : public std::shared_ptr<Particle_Base>{
public:
    template <class T>
    Particle(T* t):std::shared_ptr<Particle_Base>(t)
    {
    }

    Particle run() const;

    Particle send(pg::Dataptr inputData, pg::Datatypeptr output, pg::Entityptr context) const {
        pg::Processptr me = get()->getContext();

        pg::Future answ  = me->send(inputData, output, context);
        return Particle( new FutureParticle(context, answ));
    }
    Particle interact(Particle other) const{
        auto type = other->getType();
        auto fromType = type->getFrom();
        auto toType = type->getTo();
        auto value = other->getValue();
        auto me = get()->getContext();
   //     Particle alce2 = other.send(value, fromType,  );
        Particle alce = send(value, fromType, other->getContext() );
        return alce;

    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& data ){
        os<<"Particle:"<<data->getContext()->toString()<<" | "<<data->getType()->toString()<<" | "
                <<data->getValue()->getType()->toString()<<std::endl;
        return os;
    }


    template<class ...OUTPUT, class ...INPUT>
    Particle send(INPUT... input) const {
       pg::Processptr me = get()->getContext();

       auto answ = me->send(input...);

       Particle alce = new FutureParticle(me, answ);
        return alce;
    }


};

template <class T>
Particle makeParticle(T* t){
    Particle newParticle = Particle(t);
    return newParticle;
}




}

