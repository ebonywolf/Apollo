
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
            std::shared_ptr<Y> alceptr=std::make_shared<Y>(obj);
            all_values.push_back(alceptr);
            read=1;
        }
        std::shared_ptr<Y> at(int index)
        {
           if(all_values.size()<=index || !read)
               return std::shared_ptr<Y>(nullptr);
           return all_values[index];
        }
        int size(){
            return all_values.size();
        }
        bool read=0;
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
        if(!readerParticle->read){
            throw std::runtime_error("No values read");
        }

        std::shared_ptr<T> alce = readerParticle->at(0);
        if(alce.get() == nullptr)
            throw std::runtime_error("read null value");


        return *(alce.get());
    }
    std::vector<std::shared_ptr<T>> view_all(Particle p)
    {
        auto readerParticle = Reader<T>::get();
        Particle meParticle = makeParticle(readerParticle);

        Particle result = meParticle.interact(p);
        result->getValue(); //returns null

        return readerParticle->all_values;
    }



};

}
