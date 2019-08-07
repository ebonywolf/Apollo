#include <bits/stdc++.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Renderer.h"

#include "Node.h"
#include "Omni.h"
#include "Entity.h"
#include "Position.h"

using namespace std;
using namespace pg;

double maxY = 700;
double maxX = 700;
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
                   // Omniptr opt =grid[Position(_x,y)];
                    s->add(grid[{_x,y}]);
                    s->add(grid[{_x,_y}]);
                    s->add(grid[{x,_y}]);
                    s->add(grid[{x,y}]);
                }
                s->remove(s);
            }
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

    grid[{50,50}]->state= {0,255,0};

    Node::doShit( grid[{50,50}]);

    while ( win.running) {
    //    grid[{80,80}]->sendData(grid[{80,81}],{255,0,0});

     //   grid[{80,5}]->sendData(grid[{80,6}], {-254} );

    std::this_thread::sleep_for ( std::chrono::milliseconds ( 1000) );
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[{i,j}]->omniUpdate(  );
            }
        }
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
//                 grid[{i,j}]->doShit();
        //        segfield[i][j]->update(vals);
            }
        }
    }

}
