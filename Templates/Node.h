#pragma once
#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../Entities/SpecialEntities.h"
#include "Position.h"
namespace pg
{


struct Color{
    int r,g,b;
    bool operator==(const Color& cor){
        return r==cor.r && g==cor.g && b == cor.b;
    }

    bool operator!=(const Color& cor){
        return  !(*this==cor);
    }
    Color operator^(const Color& cor)const{
        Color c = {r^cor.r, g^cor.g, b^cor.b};
        return c;
    }

    friend
    std::ostream& operator<<(std::ostream& os, const Color c){
        os<<c.r<<" "<<c.g<<" "<<c.b;
        return os;
    }
};

struct Node : public sf::RectangleShape {
    int N;

    Node()
    {
        //  value = ramd
    }

    Node( int i, int j, double size, int n ) :
        sf::RectangleShape( sf::Vector2f( size, size ) )
    {
        pos = {   i,j };
        this->size = size;
        this->setPosition(i*size, j*size);
//        updateFunc = Node::doShit;
    }
    void update()
    {
//        Entity<Color>::omniUpdate();
    }
    void setState(Color c){
        state =c;
    }
    void warnAll()
    {

    }

    static void doShit(Entityptr me)
    {
       //
//        auto alce = std::static_pointer_cast<Node>(me);

//        unsigned char red=myval.r,green=myval.g,blue=myval.b ;
       // alce->setFillColor( sf::Color (red,green,blue) );
        //  std::cout<< "State:"<<(int)blue << std::endl;

    }
    Position pos;
    double size;
    Color state;

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
