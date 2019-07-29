#pragma once
#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Tools/Coord.h>
#include <unordered_map>
#include "Entity.h"
#include "Position.h"
namespace pg
{

struct Node : public sf::RectangleShape, public Entity<Position> {
    int N;

    Node(){
      //  value = ramd


    }
    Node( int i, int j, double size, int n ) :
        sf::RectangleShape( sf::Vector2f( size, size ) )
    {
        pos = {   i,j };
        this->size = size;
        this->setPosition(i*size, j*size);
        updateFunc = Node::doShit;

    }
    void update(){
        Entity<Position>::omniUpdate();
    //   doShit()
    }
    static void doShit(Entityptr ent){
        auto node = std::static_pointer_cast<Node>(ent);
        unsigned char red=255,green=0,blue=0;
        if(node->omniChanged){
            blue=255;
            red=0;
            node->eurusChanged=true;
        }
        node->setFillColor( sf::Color (red,green,blue) );

    }
    Position pos;
    double size;

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
