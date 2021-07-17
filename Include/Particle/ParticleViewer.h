
#pragma once
#include "Particle_Base.h"
#include "UnchargedParticle.h"
#include "Apollo.h"

namespace ap {


template<class T>
class ParticleViewer : public pg::MultiInstance<ParticleViewer<T>>
{


private:

    virtual void read_value(const T& obj) {
        throw "foo";
    }
    virtual T& return_value(){
        throw "foo";
    }
    constexpr std::string name(){
        return std::string("ParticleViewer_")+typeid(T).name();
    }
public:

    ParticleViewer(): pg::MultiInstance<ParticleViewer<T>>(name(),readFunction){
    }
    virtual ~ParticleViewer(){}
    static pg::NullType readFunction(pg::Entityptr me, const T& obj)
    {
        auto meptr = pg::cast<ParticleViewer>(me);
        meptr->read_value(obj);
        return *pg::Null();
    }


    T& view(Particle p){
        auto alce = this->get();
        Particle meParticle = makeParticle(alce);
        meParticle.interact(p);
        return return_value();
    }

};

}
