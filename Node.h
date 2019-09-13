#pragma once
#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Templates.h"
#include "Renderer.h"
#include "Coord.h"

namespace pg
{

struct NodeData
{
    sf::Color color;
    Coord size;
    Coord position;
};
using NodeDataptr = std::shared_ptr<NodeData>;

struct Node : public sf::RectangleShape,
    //    public Entity<Void, Spriteptr>,
        public CommandOriented,
        public enable_shared_from_this_virtual<Node>,
        public MultiInstance<Node>
{

//;  using nodeConn = Entity<NodeDataptr,Void>;
 // using renderConn = Entity<Void,Spriteptr>;

    NodeDataptr data;
    bool changed = false;
    Node( NodeDataptr data ) :
            sf::RectangleShape(), data( data )
    {
        auto ren = Renderer::get();
        CommandOriented::sendValue(ren, CREATE);
    }

    virtual void update(CommandOriented::Negaptr sender){
        this->setPosition( data->position.x , data->position.y );
        this->setFillColor( sf::Color( data->color ) );
        this->setSize( { data->size.x, data->size.y } );
    }
    virtual void ack(CommandOriented::Negaptr sender,  Commands cmd ){
        if(cmd.test(CREATE)){
            auto ren = Renderer::get();
            if(ren == sender){

              //  ren->add(getMe(this) );
            }else{
                throw std::runtime_error("Invalid response from renderer");
            }
        }
    }
    virtual void create(CommandOriented::Negaptr sender){

    }
    virtual void destroy(CommandOriented::Negaptr sender){
        auto ren = Renderer::get();
        CommandOriented::sendValue(ren, DESTROY);
    }


private:

};
using Nodeptr = std::shared_ptr<Node>;

}

#endif // NODE_H
