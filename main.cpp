//#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Coord.h"

#include <Apollo.h>

#include "Examples/Boxes/Box.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
using namespace pg;

struct MinhaParticulaFofinha :UniqueEntity   {

    MinhaParticulaFofinha():UniqueEntity("MinhaParticulaFofinha"){
    }

};


struct Param : public pg::GenericData<Param>{

};

struct Pai{

};
struct Tesinho : public Pai {
};
struct Geginho {
};

struct Ack: public  pg::GenericEntity<Ack>{
    Ack():GenericEntity(__CLASS_NAME__ ,doShit) {}
    static Tesinho doShit(Entityptr ptr, Geginho a){}
};




int main(int argc,char** argv)
{

    MinhaParticulaFofinha f;

 //   VariadicProcess<Ack,Param,MyTesteFofinho> v;
   // BoxDrawer::_instance;
    try{
        Particle context = ContextCreator::createFromJson("test.json");
        Particle alce= Particle(new UniqueEntity("Alce"));

        alce->addOmni(context);
        MyTesteFofinho boxinfo(1);
        Future boxmsg = alce->send<MyTesteFofinho>(boxinfo);
        alce->update();
        auto createdBox = boxmsg.getObject<MyTesteFofinho>();
        std::cout<< "answer:"<<createdBox.alce <<std::endl;

    }
    catch(Json::RuntimeError& e){
        std::cout<<e.what()<<std::endl;
    }

   // Ack ack =context->send<Ack>(box);
    return 0;
}



