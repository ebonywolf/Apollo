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
#include "Particle/ParticleViewer.h"
using namespace std;
using namespace pg;
using namespace ap;



struct Calculator: public MultiInstance<Calculator>{
	Calculator():MultiInstance(__CLASS_NAME__ ,doShit,doShit2) {}
    static double doShit(Entityptr ptr, double a,double b,double c){
        std::cout <<"Doing shit:"<<a<<" "<<b<<" "<<c <<std::endl;
        return a*b*c;
    }
    static double doShit2(Entityptr ptr, double a){
         std::cout <<"giving a shit:"<<a<<std::endl;;
         return a;
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

std::shared_ptr<double> fu(const double& alce){
    std::shared_ptr<double> alceptr = std::make_shared<double>(alce);
    return alceptr;
}


int main(int argc,char** argv)
{

    Particle calculator = ap::makeParticle(new ap::JsonParticle("test.json"));

    Particle val = calculator.send<double>(4.0);

    Particle result = calculator.send<double>(3.0, 5.0, val);

    cout<<"calc result:"<<result<<endl;
    ParticleViewer<double> resultViewer= ParticleViewer<double>();
    double resp = resultViewer.view(result);
    cout<<"viewer:"<<resp<<endl;

    std::cout <<"end" <<std::endl;

    return 0;
}



