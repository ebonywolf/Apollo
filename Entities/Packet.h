#ifndef APOLLO_PACKET_H_
#define APOLLO_PACKET_H_
#include "Data.h"
#include "Process.h"
namespace pg{



struct Packet{
    Entityptr destination;
    Dataptr data;
    Future futureAnswer;
    Entityptr context;

    Packet(Entityptr destination, Dataptr data, Future futureAnswer,Entityptr context ):
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

    int getSize(Entityptr) const;
    void push(Entityptr context,Packet p);
    PacketList pull(Entityptr context);
private:
    std::unordered_map<std::string,PacketList > _base;

};




}


#endif /* APOLLO_PACKET_H_ */
