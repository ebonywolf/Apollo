#pragma once
#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Entity.h"
#include "Coord.h"
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


struct NodeData{
    Color color;
    Coord size;
    Coord position;
};
using NodeDataptr = std::shared_ptr<NodeData>;




struct Node : public sf::RectangleShape, public Entity<NodeData,Void>, public MultiInstance<Node> {
    using nodeConn = Entity<NodeData,Void>;

    int N;

    Node(): sf::RectangleShape()
    {
        nodeConn::setRunFunction(draw);
    }
/*
    Node( double i, double j, double size, int n ) :
        sf::RectangleShape( sf::Vector2f( size, size ) )
    {
        pos = {   i,j };
        this->size = size;
        this->setPosition(i*size, j*size);
        updateFunc = Node::doShit;
    }
    */
    void update()
    {
    }
    void setState(Color c){
        state =c;
    }


    static void draw(nodeConn::Entityptr me)
    {
        auto root = getRoot(me);
        auto changed = me->getChanged();
       // Strtuple val = changed->getValue(me);


      //  unsigned char red=myval.r,green=myval.g,blue=myval.b ;
      //  alce->setFillColor( sf::Color (red,green,blue) );


    }
    Coord pos;
    double size;
    Color state;

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
