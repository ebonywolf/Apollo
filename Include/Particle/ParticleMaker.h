#pragma once

#include "Particle.h"
#include <Apollo.h>

namespace ap{

namespace Tools{

}




template <class T>
Particle makePrimitive(const T& t,std::false_type){
throw "todo";
}

template <class T>
Particle makePrimitive(const T& t,std::true_type){
    pg::Entityptr entity = pg::PrimitiveEntity<T>::get();
    // pg::PrimitiveEntity<T>::get(t);

    pg::Dataptr data = std::make_shared<pg::Primitive_Data<T>>(t);

            //

            //
   // Particle_Base* unch = new ap::UnchargedParticle(entity) ;
  //  return Particle(unch);
}


template <class T>//Particle_Base
Particle makeParticle(const T& t){
    return makePrimitive(t,std::is_fundamental<T>());
}
template <class T>//Particle_Base
Particle makeParticle(T* t){


}

template <class T>//Particle_Base
Particle makeParticle(std::shared_ptr<T> t){

}

template <class ...T>//Particle_Base
Particle makeParticle(T ...t){

}





}
