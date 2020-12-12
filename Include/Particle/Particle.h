#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include "Core/Base.h"
#include "Entity/Entity.h"
#include "DataType/DataTuple.h"

#include "DataType/GenericDatatype.h"
namespace ap{



class Particle_Base;
using Particle = std::shared_ptr<Particle_Base>;

class Particle_Base: public enable_shared_from_this_virtual<Particle_Base>{
public:
    virtual pg::Entityptr getEntity() = 0;

    template<class ...OUTPUT, class ...INPUT>
    Particle send(INPUT... input){
        pg::DataTuple<INPUT...> inputData(input...);
        pg::DataTuple<OUTPUT...> output();

        pg::Entityptr me = getEntity();
        me->send(inputData, output.getType(), me);
    }

};



using Particle = std::shared_ptr<Particle_Base>;

template <class T>
Particle makeParticle(T* t){
    Particle newParticle = new std::shared_ptr<Particle_Base>(t);
    return newParticle;
}




}

#endif //PARTICLE_H
