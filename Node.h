#pragma once
#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Entity.h"
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


struct Node : public sf::RectangleShape, public Entity<Color> {
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
        updateFunc = Node::doShit;
    }
    void update()
    {
        Entity<Color>::omniUpdate();
    }
    void setState(Color c){
        state =c;
    }
    void warnAll()
    {
        for( auto& it: getEntities() ) {
            auto x = it.first;
            sendValue(x, state );
        }
    }

    static void doShit(Entityptr me)
    {
        auto alce = std::static_pointer_cast<Node>(me);
        Color& myval = alce->state;
        auto previousVal=myval;

        bool emit = false;
        auto changed = me->getChangedEntities() ;
        for(auto& it: changed)
        {
            auto node = it;
            auto val = node->getValue(me);
         //   auto val = it.second;
            if(previousVal!=val){
               myval = val;
               emit = true;
            }
        }
       // std::cerr<<"Painting:"<<alce->pos<< " with "<< myval <<std::endl;
        if(emit){
            auto& entities=me->getEntities() ;
            for(auto& it: entities)
            {
                auto node = it.first;
                auto alce = std::static_pointer_cast<Node>(me);
           //     std::cerr<<"Sending it to:"<<alce->pos<<std::endl;
                auto val = it.second;
                if(myval!=val){
                    me->sendValue(node, myval);
                }
            }
        }


        unsigned char red=myval.r,green=myval.g,blue=myval.b ;
        alce->setFillColor( sf::Color (red,green,blue) );
        //  std::cout<< "State:"<<(int)blue << std::endl;

    }
    Position pos;
    double size;
    Color state;

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
