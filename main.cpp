#include <bits/stdc++.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Renderer.h"

#include "Node.h"
#include "Entity.h"
#include "Position.h"

using namespace std;
using namespace pg;

double maxY = 900;
double maxX = 900;
int N = 100;

//Entity<Position> enti;
using Omniptr = std::shared_ptr< Node>;

std::unordered_map<Position, Omniptr > grid;

int fromCoord( int i, int j, int n )
{
    int var = i * n + j;
    return var;
}

void populateGrid( double n )
{
    double varX = maxX / n;
    double varY = maxY / n;
    for ( int i = 0 ; i < n ; i++ ) {
        for ( int j = 0 ; j < n ; j++ ) {
            Position p={i,j};
            auto alce = shared_ptr<Node>( new Node( i, j, varX,N ) );
              grid[p] =  alce;

        }
    }
}
int mod(int a,int b)
{
    return(b + (a%b)) % b;
   // if(a<0)return 0;
 //   if(a>=b)return b-1;
    return a;

}

void populateSegs(int segs)
{

    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < N ; j++ ) {
          //  auto s= make_shared<Omni<Position>>();
            auto s = grid[{i,j}];


            for (int w=0; w<= segs ; w++ ) {
                for (int z=0; z<= segs ; z++ ) {
                    if(abs(w) + abs(z)>segs)
                        continue;

                    int x = mod(i + w,N);
                    int _x =mod( i - w,N);
                    int y = mod(j +z,N);
                    int _y =mod( j-z,N);
                    Position a = {_x,y};
                     Position b = {_x,_y};
                     Position c = {x,_y};
                     Position d = {x,y};

                   // Omniptr opt =grid[Position(_x,y)];
                    s->add(grid[a]);
                    s->add(grid[b]);
                    s->add(grid[c]);
                    s->add(grid[d]);
                }
            }

            s->remove(s);


        }
    }
}


int mysin(int a){
    double y= sin(a)*100;
    return y;
}

struct A{
    A(){}
    int x;
};
using Aptr = std::shared_ptr<A>;

std::unordered_map<Aptr,int> mapa;

void func(int cont){
static bool started = false;


if(cont<300){
    std::cerr<<cont<<std::endl;
    return;
}
std::cerr<<grid[{90,1}]->state<<std::endl;
//if(grid[{90,1}]->state == {0,0,255})return
grid[{90,1}]->setState( {0,0,255});
grid[{90,1}]->warnAll();

 for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[{i,j}]->omniUpdate(  );
            }
        }
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[{i,j}]->eurusUpdate(  );

            }
        }
}


int main()
{

    srand(time(0));
    Renderer win = Renderer( { maxX, maxY } );

    populateGrid( N );
    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < N ; j++ ) {
            win.add( grid[{i,j}] );
        }
    }
    populateSegs(1);
    std::cout << "Starting" << std::endl;
    win.beginAssync();
    win.running=true;

    int i =0;


    grid[{9,1}]->setState( {0,255,0});
    grid[{9,1}]->warnAll();

    grid[{90,1}]->setState( {0,0,255});
    grid[{90,1}]->warnAll();

    int cont=0;
    while ( win.running) {
           // std::cerr<<cont<<std::endl;
            func(cont++);
    //  std::this_thread::sleep_for ( std::chrono::milliseconds ( 800) );
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[{i,j}]->omniUpdate(  );
            }
        }
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[{i,j}]->eurusUpdate(  );

            }
        }
    }

}
