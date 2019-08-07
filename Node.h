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



struct Node : public sf::RectangleShape, public Entity<std::array<unsigned char,3>> {
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
        Entity<std::array<unsigned char,3>>::omniUpdate();
    }

    static void doShit(Entityptr me)
    {
        auto node = std::static_pointer_cast<Node>(me);
        auto& myval = node->state;

        //    myval = !myval;

        auto previousVal=myval;

        for( auto& it: me->getChangedEntities() ) {
            auto x = it;
            auto val = x->getValue(me);
            for (int i = 0; i < 3; i++) {
                myval[i]=  (myval[i] ^val[i]);
            }
        }

        bool changed=0;
        for (int i = 0; i < 3; i++) {
            if( previousVal[i] != myval[i] ) {
                changed = true;
            }
        }




        unsigned char red=myval[0],green=myval[1],blue=myval[2] ;
        node->setFillColor( sf::Color (red,green,blue) );
        if(me->getChangedEntities().size()==0) {
            for( auto& it: me->getEntities() ) {
                auto x = it.first;
                me->sendData(x, myval );
            }
        }else{
            if(changed){
                for( auto& it: me->getEntities() ) {
                    auto x = it.first;
                }
            }

        }


        //  std::cout<< "State:"<<(int)blue << std::endl;

    }
    Position pos;
    double size;
    std::array<unsigned char,3> state;

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
