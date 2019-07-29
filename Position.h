#pragma once

#include <functional>
namespace pg{

struct Position{
    int x,y;
    Position(){};
    Position(int x, int y):x(x),y(y){}
    bool operator==(const Position& p)const {
        return p.x ==x && p.y==y;
    }
};


}


namespace std {

  template <>
  struct hash< pg::Position>
  {
    std::size_t operator()(const pg::Position& k) const
    {
      auto alce =std::hash<int>();

      return alce(k.x ^ k.y);
    }
  };
}
