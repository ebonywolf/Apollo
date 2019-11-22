#ifndef APOLLO_PACKET_H_
#define APOLLO_PACKET_H_
#include "Data.h"
#include "Process.h"
namespace pg{

struct Packet{
    Processptr destination;
    Dataptr data;
    Future futureAnswer;
    Processptr context;

    Packet(Processptr destination, Dataptr data, Future futureAnswer,Processptr context ):
        destination(destination),
        data(data),futureAnswer(futureAnswer),context(context)
    {
    }
    DataPair getChannel()const {
        return DataPair(futureAnswer->getType(), data->getType());
    }
};


using PacketList = std::vector<Packet>;

struct PacketMap   {

    int getSize(Processptr) const;
    void push(Processptr context,Packet p);
    PacketList pull(Processptr context);
private:
    std::unordered_map<std::string,PacketList > _base;

};

}


#endif /* APOLLO_PACKET_H_ */
