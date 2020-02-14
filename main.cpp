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


struct Dado{

};

struct Ack: public  pg::GenericEntity<Ack>, public MultiInstance<Ack>{
    Ack():GenericEntity(__CLASS_NAME__ ,doShit) {}
    static double doShit(Entityptr ptr, double a, double b){
        return a*b;
    }
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
        alce->addOmni(Ack::get());

        double d=9;
        Future boxmsg = alce->send<double>(d,d);
        alce->update();
//        auto answer = boxmsg.getObject<float>();

//        std::cout<< "answer:"<<answer <<std::endl;

    }
    catch(Json::RuntimeError& e){
        std::cout<<e.what()<<std::endl;
    }

   // Ack ack =context->send<Ack>(box);
    return 0;
}



