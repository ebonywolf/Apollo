#ifndef APOLLO_PACKET_H_
#define APOLLO_PACKET_H_
#include <Apollo.h>


namespace pg{

struct Packet{
    Dataptr data;
    Future futureAnswer;
    Processptr context;

    Packet( Dataptr data, Future futureAnswer,Processptr context ):
        data(data),futureAnswer(futureAnswer),context(context)
    {
    }
    Datatypeptr getChannel()const {
        return Datatypeptr(
                new DataPair(futureAnswer->getType(), data->getType() )
        );
    }
};


using PacketList = std::vector<Packet>;

struct PacketMap   {

    int getSize(Processptr) const;
    void push(Processptr context,Packet p);
    PacketList pull(Processptr context);
private:
    std::unordered_map< Datatypeptr,PacketList, HashFunction> _base;

};

}


#endif /* APOLLO_PACKET_H_ */
