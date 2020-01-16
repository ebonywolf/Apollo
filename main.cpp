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

struct MinhaParticulaFofinha : public UniqueEntity   {

    MinhaParticulaFofinha():UniqueEntity("MinhaParticulaFofinha"){
    }

};


int main(int argc,char** argv)
{
    MinhaParticulaFofinha f;
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

