//#include <bits/stdc++.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coord.h"
#include "Entities/Process.h"
#include "Entities/SpecialEntities.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
using namespace pg;
/*
sf::Color defaultColor = sf::Color(255,0,0,255);
Coord defaultSize = Coord(5,5);

int MAX_Y=500;
Renderer renderer = Renderer({500,MAX_Y});;

vector<Spriteptr> sprites;

struct Square: public sf::RectangleShape {
    Square(Coord size, Coord position, sf::Color color)
    {
        this->setPosition( position.x, position.y );
        this->setFillColor( sf::Color( color ) );
        this->setSize( { size.x, size.y } );
    }
};
Spriteptr createSquare(Coord position, Coord size)
{
    position.y = MAX_Y - position.y;
    Spriteptr sprite = Spriteptr(new Square( size, position,defaultColor));
    sprites.push_back(sprite);
    return sprite;
}

void drawCurve(Axles axles, double maxPrecision=100)
{
    for (int i=0; i<axles.size() -1; i++) {
        Coord current = axles[i];
        Coord next = axles[i+1];
        double xvar = (next.y - current.x)/maxPrecision;
        for (double precision=0; precision < maxPrecision; precision++) {
            double x_position =  current.x + xvar*precision ;
            Coord currentPosition = {x_position, 10};
            renderer.add(createSquare(currentPosition,defaultSize));

            for (int j=0; j<axles.size(); j++) {
                if(i==j)
                    continue;
                Coord j_axle = axles[j];

                double size = axles.size();
                //       double totalDistance= current.distance(x_position);
                //totalDistance+= j_axle
            }
        }
        // Coord position = {current.x}
    }
}

*/

inline std::string className(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
        return "::";
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = colons - begin;
    return prettyFunction.substr(begin,end);
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)


struct Ack: public GenericData<Ack>{
    int a;
    Ack(){}
    Ack(int a):a(a){}
};

struct BoxInfo: public GenericData<BoxInfo>{
    pg::Coord pos,dim;
    friend ostream& operator<<(ostream& os, const BoxInfo& b){
        os<<b.pos;
        return os;
    }

};



class Box: public BoxInfo,  public GenericEntity<Box>{
public:

    Box():GenericEntity(__CLASS_NAME__,boxCreator  ){

    }

    Box(BoxInfo& b):BoxInfo(b){
    }


    static Ack boxCreator(Myptr me, BoxInfo box){
        std::cout<< "Me:"<<me->getHashKey() <<std::endl;
        //shared_ptr<Box> b = make_shared<Box>(box);
        //return b;
        return Ack(666);
    }


};
using Boxptr = std::shared_ptr<Box>;

class BoxDrawer: public GenericEntity<BoxDrawer>{
public:

    BoxDrawer():GenericEntity(__CLASS_NAME__,creator){
    }

    static std::shared_ptr<Box> creator(Myptr me, BoxInfo info){
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
        std::cout<<"Got box:"<<info<<std::endl;

        return std::make_shared<Box>(info);
    }

};



int main(int argc,char** argv)
{

   // BoxDrawer::_instance;
    try{
        Particle context = ContextCreator::createFromJson("test.json");
        Dataptr box = make_shared<BoxInfo>();
        Particle alce= Particle(new UniqueEntity("Alce"));
        alce->addOmni(context);

        Future f = alce->send<std::shared_ptr<Box>>(box);
        alce->update();

        auto c = f.getObject<std::shared_ptr<Box>>();
        std::cout<< "Result:"<<c << std::endl;
    }
    catch(Json::RuntimeError& e){
        std::cout<<e.what()<<std::endl;
    }

   // Ack ack =context->send<Ack>(box);

    return 0;
}
