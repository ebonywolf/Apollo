#pragma once

#include <bitset>

#include "../Entities/Entity.h"
#include "Specials.h"

namespace pg
{

enum CommandEnum
{
    NOTHING, CREATE, DESTROY, UPDATE, ACK, LAST_CMD
};
using Commands = std::bitset<LAST_CMD>;

template<class T>
struct CommandOriented
{

    CommandOriented()
    {
   //     CommandOriented::setRunFunction( runCmd );
    }
    virtual ~CommandOriented()
    {
    }


};

}




