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
#include "Include/Particle/JsonParticle.h"

using namespace std;
using namespace pg;
using namespace ap;


struct Calculator: public MultiInstance<Calculator>{
	Calculator():MultiInstance(__CLASS_NAME__ ,doShit) {}
    static double doShit(Entityptr ptr, double a){
        return a*2;
    }

};

struct Main : public Singleton<Main>{
    Main():Singleton(__CLASS_NAME__ ,relay,lie,truth) {}

    //Requesting AllType  Sending NullType

    static pg::NullType relay(Entityptr ptr, pg::NullType  ){
        std::cout <<"hello world" <<std::endl;
        std::cout <<"OmniSet:"<<ptr->getOmni()->toString() <<std::endl;
        std::cout <<"EurusSet:"<<ptr->getEurus()->toString() <<std::endl;

     //   auto number = ptr->getOmni("Console");
        return pg::NullType();
    }
    static pg::AllType lie(Entityptr ptr, pg::NullType  ){
          std::cout <<"Begin world" <<std::endl;
          return pg::AllType();
    }
    static pg::AllType truth(Entityptr ptr, pg::AllType  ){
          std::cout <<"hello god" <<std::endl;
          return pg::AllType();
    }


};

int main(int argc,char** argv)
{
    Particle context = ap::makeParticle(new ap::JsonParticle("test.json"));
    Particle result = context.send<double>(3.0);
 //   Particle result = context.run();
     cout<<result;
       // auto Main = context->getEntity("Main");


    return 0;
}



