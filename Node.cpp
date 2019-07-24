
#include "Node.h"
using namespace std;


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

namespace pg{

static int mod(int a,int b)
{
    return(b + (a%b)) % b;
}

void Segment::add(Nodeptr n){
    connections[n]=0;
 //   n->connections[shared_from_this()]=0;
}
void Segment::setOwner(std::shared_ptr<Node> n){
    owner = n;
    connections.erase(n);
}


void Segment::update(CampoVals& vals){
   // value/= connections.size();
   vector<Nodeptr> toUpdate;
     if(value <0){
        int a=0;
     }
   int res=0;

   int conMax =0;
   double weightTotal=0;
   for (auto& it: connections) {

        auto node= it.first;
        auto& val = it.second;
        val = node->weightValue;
        auto destValu = vals[node->pos.x][node->pos.y];
        auto dpp = destValu - value;

        conMax+=dpp;
        weightTotal+=node->weightValue;
   }
   owner->weightValue=weightTotal/(double)connections.size();

   Nodeptr choice = connections.begin()->first;
   int alce= 0;
   vector<Nodeptr> nodeList;
   for (auto& it: connections) {
        auto node= it.first;
        auto val = node->weightValue;
        auto destValu = vals[node->pos.x][node->pos.y];
        auto dpp = destValu - value;
        if(val == alce){
            nodeList.push_back(node);
        }
         if(val > alce){
            nodeList.clear();
            nodeList.push_back(node);
            alce = val;
        }
    }
    for(auto x: nodeList){
        x->send(shared_from_this(), -value);
    }
    // choice->send(shared_from_this(), value);


    value=0;
   //max
}


void  Segment::send(Nodeptr origin, int val){
   value +=val;
 //  connections[origin]--;
 }

void Node::send(SegmentPtr seg, int val){
    value+=val;
   // connections[seg]+=val;
}

void Node::update(CampoVals& vals)
{
    if(value<0) {
        double red = value*-50;
        if(red>254)
            red=254;
        double green = this->weightValue*10;

        this->setFillColor( sf::Color (red,green,0) );
    } else {
        double red = value*50;
        if(red>254)
            red=254;
       double green =this->weightValue*10;
        this->setFillColor( sf::Color (0,green,red) );
    }
   // if(value>0 && weightValue>1){
        auto alce = value;
       // value -= weightValue;
  //      weightValue+=(abs(alce));
   // }
   // weightValue-=value;

    SegmentPtr choice;

    int weight = 999999;
   // std::cerr<<connections.size()<<std::endl;
    for (auto& it: connections) {
        auto& wei = it.second;
        auto con = it.first;
        if(value>0){
            int a=0;
        }
        con->send(shared_from_this(),value);

    }
      value = 0;
   //choice->send( shared_from_this(), value );

}

std::vector<Coord> Node::getNeighs()
{
    int bx = before(pos.x);
    int ax= next(pos.x);
    int by = before(pos.y);
    int ay = next(pos.y);
    vector<Coord> neighs;
    neighs.push_back( {bx,pos.y} );
    neighs.push_back( {ax,pos.y} );
    neighs.push_back( {pos.x,by} );
    neighs.push_back( {pos.x,ay} );
    return neighs;
}



}
