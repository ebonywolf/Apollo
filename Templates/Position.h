#pragma once

#include <functional>
namespace pg{

struct Position{
    int x,y;
    Position(){};
    Position(int x, int y):x(x),y(y){}
    bool operator==(const Position& p)const {
        return p.x == x && p.y==y;
    }
    friend
    std::ostream& operator<<(std::ostream& os, const Position c){
        os<<c.x<<" "<<c.y;
        return os;
    }
};


}

