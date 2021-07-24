
#pragma once
#include "Particle_Base.h"
#include "UnchargedParticle.h"
#include "Apollo.h"

namespace ap {


template<class T>
class ParticleViewer
{
    template <class Y>
    struct Reader: public pg::MultiInstance<Reader<Y>>
    {
        Reader():pg::MultiInstance<Reader<Y>>(name(),readFunction){

        }
        void read_value(const Y &obj)
        {
            std::cout <<"reading shit" <<std::endl;
            std::shared_ptr<Y> alceptr=std::make_shared<Y>(obj);
           all_values.push_back(alceptr);
        }
        std::shared_ptr<Y> at(int index)
        {
            std::cout <<"returning shit" <<std::endl;
           if(all_values.size()<=index)
               return std::shared_ptr<Y>(nullptr);
           return all_values[index];
        }
        int size(){
            return all_values.size();
        }
        std::vector<std::shared_ptr<Y>> all_values;
    };

private:
    static constexpr std::string name(){
        return std::string("ParticleViewer_")+typeid(T).name();
    }
protected:

public:

    ParticleViewer(){}
    virtual ~ParticleViewer(){}

    static pg::NullType readFunction(pg::Entityptr me, T obj)
    {
        std::cout <<"yay" <<std::endl;
        std::cout <<"reading"<<obj <<std::endl;
        auto meptr = pg::cast<Reader<T>>(me);
        meptr->read_value(obj);
        return *pg::Null();
    }

    T view(Particle p){
        auto readerParticle = Reader<T>::get();
        Particle meParticle = makeParticle(readerParticle);

        Particle result = meParticle.interact(p);
        result->getValue();//returns null
        std::shared_ptr<T> alce = readerParticle->at(0);
        if(alce.get() == nullptr)throw "foo";

        return *(alce.get());
    }
    std::vector<std::shared_ptr<T>> view_all(Particle p){

    }
    std::vector<std::shared_ptr<T>> all_values(){

    }


};

}
