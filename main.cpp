#include <bits/stdc++.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Renderer.h"

#include "Node.h"
using namespace std;
using namespace pg;

double maxY = 1000;
double maxX = 1000;
int N = 300;


vector<vector<shared_ptr<Node>>> grid;
SegmentField segfield;
int fromCoord( int i, int j, int n )
{
    int var = i * n + j;
    return var;
}

void populateGrid( double n )
{
    double varX = maxX / n;
    double varY = maxY / n;
    grid.resize( n );
    for ( int i = 0 ; i < n ; i++ ) {
        grid[i].resize( n );
        for ( int j = 0 ; j < n ; j++ ) {
            grid[i][j] = shared_ptr<Node>( new Node( i, j, varX,N ) );

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
            auto s= make_shared<Segment>();

            for (int w=0; w<= segs ; w++ ) {
                for (int z=0; z<= segs ; z++ ) {
                    if(abs(w) + abs(z)>segs)
                        continue;

                    int x = mod(i + w,N);
                    int _x =mod( i - w,N);
                    int y = mod(j +z,N);
                    int _y =mod( j-z,N);
                    s->add(grid[_x][y]);
                    s->add(grid[_x][_y]);
                    s->add(grid[x][_y]);
                    s->add(grid[x][y]);
                }
            }
            s->setOwner( grid[i][j]);
            grid[i][j]->connections[s]=0;
            segfield[i][j]=s;
        }
    }


}

CampoVals getVals()
{
    CampoVals vals;
    vals.resize( N );
    for ( int i = 0 ; i < N ; i++ ) {
        vals[i].resize( N );
        for ( int j = 0 ; j < N ; j++ ) {
            vals[i][j] = grid[i][j]->value;
        }
    }
    return vals;
}

int main()
{

    srand(time(0));
    Renderer win = Renderer( { maxX, maxY } );

    populateGrid( N );
    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < N ; j++ ) {
            win.add( grid[i][j] );
        }
    }
    populateSegs(1);
    std::cout << "Starting" << std::endl;
    win.beginAssync();


    int i =0;

   while ( true) {
    grid[15][15]->weightValue=50000;
     // grid[150][150]->value=50;
        i++;
   //  grid[1][1]->weightValue=200;
   //
  // std::cerr<<"hello"<<std::endl;
     grid[5][7]->value=10;
     grid[50][50]->value=10;
    // grid[40][40]->weightValue=10000;


     //   grid[0][0]->value=i;
      //  grid[0][5]->value=i*i-4;

      //     grid[0][2]->value=-1;
     //   std::this_thread::sleep_for ( std::chrono::milliseconds ( 1000) );
        CampoVals vals = getVals();

        // win.begin();
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                grid[i][j]->update( vals );
            }
        }
        for ( int i = 0 ; i < N ; i++ ) {
            for ( int j = 0 ; j < N ; j++ ) {
                segfield[i][j]->update(vals);
            }
        }
    }

}
