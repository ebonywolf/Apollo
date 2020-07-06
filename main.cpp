//#include <bits/stdc++.h>
//#include <SFML/Graphics.hpp>

#include <iostream>
#include "Coord.h"

#include <Apollo.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
using namespace pg;





struct MinhaEntidadeFofinha: public MultiInstance<MinhaEntidadeFofinha>{

    MinhaEntidadeFofinha():MultiInstance(__CLASS_NAME__ ,doShit) {}

    static double doShit(Entityptr ptr, double a, double b){
        return a*b;
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
      

        Future fut2 = alce->send<double>(8.0, answer);
        alce->update();

        std::cout<< "answer:"<< fut2.getObject<double>() <<std::endl;

      
    }
    catch(Json::RuntimeError& e){
        std::cout<<e.what()<<std::endl;
    }

   // Ack ack =context->send<Ack>(box);
    return 0;
}



