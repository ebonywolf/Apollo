//#include <bits/stdc++.h>
//#include <SFML/Graphics.hpp>

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


struct Dado{

};

struct MinhaEntidadeFofinha: public  pg::GenericEntity<MinhaEntidadeFofinha>, public MultiInstance<MinhaEntidadeFofinha>{

    MinhaEntidadeFofinha():GenericEntity(__CLASS_NAME__ ,doShit,writeShit) {}

    static double doShit(Entityptr ptr, double a, double b){
        return a*b;
    }
     static double writeShit(Entityptr ptr, std::string a){

        std::cout<<a<<std::endl;
        return 5;
    }
};





int main(int argc,char** argv)
{

   try{
        //Particle context = ContextCreator::createFromJson("test.json");
        Particle alce= Particle(new UniqueEntity("Alce"));

       // alce->addOmni(context);
        alce->addOmni(MinhaEntidadeFofinha::get());

        Future fut = alce->send<double>( std::string("Hello world"));
        alce->update();

        auto answer = fut.getObject<double>();
      
        Future fut2 = alce->send<double>(fut ,8.0);
        alce->update();

        std::cout<< "answer:"<<fut2.getObject<double>() <<std::endl;

      
    }
    catch(Json::RuntimeError& e){
        std::cout<<e.what()<<std::endl;
    }

   // Ack ack =context->send<Ack>(box);
    return 0;
}



