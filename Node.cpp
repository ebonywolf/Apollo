
#include "Node.h"
using namespace std;


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define G_STR 1
namespace pg
{

static int mod(int a,int b)
{
    return(b + (a%b)) % b;
}
/*
void Node::update(CampoVals& vals)
{
    unsigned char red=0,green=0,blue=0;

    this->setFillColor( sf::Color (red,green,blue) );

}
*/
/*
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

*/


}
