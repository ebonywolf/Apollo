#pragma once

#include <bitset>

#include "Entity.h"
#include "Specials.h"

namespace pg
{

enum CommandEnum
{
    NOTHING, CREATE, DESTROY, UPDATE, ACK, LAST_CMD
};
using Commands = std::bitset<LAST_CMD>;

struct CommandOriented : public Entity<Commands, Commands>, private Common<CommandOriented>
{

    CommandOriented()
    {
        CommandOriented::setRunFunction( runCmd );
    }
    virtual ~CommandOriented()
    {
    }
    Commands buffer;

    static void runCmd( CommandOriented::Entityptr me )
    {
        auto root = getRoot( me );
        for ( auto sender : me->changedEntities )
        {
            root->buffer = sender->getValue( me );

            if (root-> buffer.test( UPDATE ) ) root->update( sender  );
            if (root->buffer.test( CREATE ) ) root->create( sender  );
            if ( root->buffer.test( DESTROY ) ) root->destroy( sender  );

            if ( root->buffer.test( ACK ) )
                root->ack( sender ,  root->buffer );
            else
            {
                root->buffer.set(ACK);
            }
            if(root->buffer.any()){
                me->sendValue( sender , root->buffer  );
            }

        }
    }
    inline void setResponse(CommandEnum e){
        buffer.set(e);
    }
    void sendValue(CommandOriented::Negaptr him, CommandEnum e) {
        Commands cmd;
        cmd.set(e);
        this->sendValue(him, e);
    }
    virtual void update( CommandOriented::Negaptr sender )=0;
    virtual void ack( CommandOriented::Negaptr sender , Commands cmd )=0;
    virtual void create( CommandOriented::Negaptr sender )=0;
    virtual void destroy( CommandOriented::Negaptr sender )=0;

};

}
/*

 template<INPUT,OUTPUT>
 struct FunctionEntity  :public Entity<std::string, StopData>,  public pg::MultiInstance<InputParser>  {

 };


 auto createFunction


 */

