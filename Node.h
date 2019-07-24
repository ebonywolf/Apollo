#pragma once
#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <Tools/Coord.h>
#include <unordered_map>
using std::vector;
using std::shared_ptr;
namespace pg
{

class Node;
class Segment;

using Campo =vector<vector< shared_ptr<Node>>>;
using Nodeptr = std::shared_ptr<Node>;
using CampoVals = vector<vector<double>>;
using SegmentField = std::unordered_map<int, std::unordered_map<int,std::shared_ptr<Segment>>>;

struct Segment: public std::enable_shared_from_this<Segment> {

    std::unordered_map<std::shared_ptr<Node>, int> connections;
    Segment(){
    };
    void add(Nodeptr n);
    int value=0;
    void send(Nodeptr origin, int val);
    void setOwner(std::shared_ptr<Node>);
    void update(CampoVals& vals);
    void remove(Nodeptr n);
    std::shared_ptr<Node> owner;

};
using SegmentPtr = std::shared_ptr<Segment>;


struct Node : public sf::RectangleShape,std::enable_shared_from_this<Node> {
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
        double val = rand()%3 -1;
   //     value = val*5;
        N = n;
        //    setFillColor( sf::Color (255/(i+1),255/(j+1),0));
    }


    Coord pos;
    double size;
    int value=0;
    double weightValue=0;
    int newVal=0;
    int next(int x)
    {
        return (x+1)%N;
    }
    int before(int x)
    {
        int alce = x-1;
        if(alce<0)
            alce*=-1;
        return (alce%N);
    }

    std::vector<Coord> getNeighs();

    void send(SegmentPtr, int);

    void update(CampoVals& vals);
    std::unordered_map<SegmentPtr,int> connections;

};
}

#endif // NODE_H
