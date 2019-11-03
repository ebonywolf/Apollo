#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <fstream>
#include <future>
#include <iostream>
#include <json/json.h>
#include "Data.h"
#include "Process.h"

namespace pg
{

struct EntityptrHash{
    std::size_t operator()(const pg::Entityptr& k) const;
};


struct EntitySet: std::unordered_set<Entityptr,EntityptrHash>
{
    bool contains(std::string name) const;
    Entityptr get(std::string name) const;

};

struct EntityMap : public std::unordered_map<DataPair,EntitySet> {
    using  std::unordered_map<DataPair,EntitySet>::unordered_map;

    EntitySet& operator()(const Datatype& from,const Datatype& to)
    {
        DataPair par (from,to);
        return operator [] (par);
    }
    const  EntitySet& operator()(const Datatype& from,const Datatype& to) const
    {
        DataPair par (from,to);
        if(!count(par))throw "foo";
        return at(par);
    }
};


struct Entity_Base : public enable_shared_from_this_virtual<Entity> {

};


struct Packet{
    Entityptr from;
    Entityptr to;
    Dataptr data;
    DataPair channel;
    Packet(){
    }
    Packet(Entityptr from,Entityptr to , Dataptr data, DataPair channel):
        from(from),to(to),
        data(data),channel(channel){

    }
};

#define GLOBAL "_Global"

struct Entity : Entity_Base  {//Defines object that runs many functions and has many dataTypes
    using ContextMap = std::unordered_map<std::string,Entityptr>;
    using SendBuffer = std::unordered_map<Entityptr, std::unordered_map<Entityptr,Packet>>;
    using PacketList = std::vector<Packet>;

    PacketList sentData;
    PacketList receivedData;

   // SendBuffer _sentBuffer;
    EntitySet _omni;
    EntityMap _eurus;
    ProcessList processes;



    template <class INPUT, class OUTPUT>
    void addProcess( OUTPUT(func)(INPUT) )
    {
        Processptr p = Processptr (new GenericProcess<INPUT,OUTPUT>(func));
        processes.insert(p);
    }


    template <class INPUT, class OUTPUT,class ...T>
    void addProcess(OUTPUT(func)(INPUT), T ...t)
    {
        addProcess(func);
        addProcess(t...);
    }

    ProcessList getProcess() const
    {
        ProcessList alce = processes;
        for(auto& it: _eurus)
        {
            Processptr novo = std::make_shared<Process>(it.first);
            alce.insert(novo);
        }
        return alce;
    }
    bool hasMethod(Datatype from, Datatype to) const
    {
        DataPair par (from,to);
        return hasMethod(par);
    }
    bool hasMethod( DataPair par ) const
    {
        return processes.count(par) || _eurus.count(par);
    }
    bool hasOmni(std::string name) const
    {
        return _omni.contains(name);
    }
    void addOmni(std::string name,const Entityptr obj)
    {
        _omni.insert(obj);
    }

    void addEurus( const Entityptr obj);
    void omniUpdate(const Entityptr context)
    {
/*
        for(auto& it : _sentBuffer[context] )
        {
            auto to = it.first;
            auto data = it.second;
            to->receiveData(shared_from_this(), data);
        }
        */
    }

    template<class T>
    Data& send( Dataptr sentData, Entityptr context=getGlobal() )
    {
        T received;
        const auto fromType = received.getType();
        const auto toType = sentData->getType();
        DataPair pair(fromType, toType);
        DataPair reversePair = pair.getInverse();

        bool sent=false;
        for (auto& it: _omni) {
            auto to = it.second;
            if(to->hasMethod(reversePair)) {
                sent=true;
            }
            Packet packet(this->shared_from_this(),to,sentData,reversePair  );
            context->sendPacket(packet);

        }
        if(!sent) {
            throw std::runtime_error(std::string("no handler for: ")+reversePair.getHashKey());
        }
    }
    void receiveData(Entityptr from, Packet data)
    {
        auto channel = data.channel;
        if(_eurus.count(channel))throw "Unhandled Method";

       std::cout<< "Received Data from:"<<from->getName()<<" Data: "<<data.data->getType() <<std::endl;
      //  changedEntities.insert(ptr);
       //   omniChanged=true;
        //  GlobalRunner::get()->addEurus( this->shared_from_this());
    }

    void extend(Entityptr other){
        addEurus(other);
        for(auto& x: other->_omni)
        {
            std::string name=x.first;
            auto otherOmni = x.second;
            addOmni(name,otherOmni);
        }
    }

    virtual std::string getName() const
    {
        throw "Its actually pure virtual method, it must be extended";
    }

    Entityptr getOmni(std::string name) const
    {
        if(_omni.count(name)) {
            return _omni.at(name);
        } else {
            throw std::runtime_error(std::string("entity not present in context: ")+name);
        }
    }


    void sendPacket(Packet ent)
    {
        packets
    }
    void addReceiver(Entityptr ent, Packet)
    {
        receivedData.insert( ent );
    }

    void update(){
        for(auto& pack:sentData)
        {
           // ent->omniUpdate(shared_from_this());
        }
    }


    static Entityptr getGlobal()
    {
        static Entityptr global;
        if(!global) {
            global = Entityptr(new Entity());
            // global->["GLOBAL"] = global;//shared ptr pointing to itself,
        }
        return global;
    }

protected:
    Entity()
    {
    };

    template <class ...T>
    Entity(T...t)
    {
        addProcess(t...);
    };

    struct PlaceHolder {
        PlaceHolder(){
        }
    };

    template<class T>
    static PlaceHolder createGlobalEntity(){
        Entityptr novo = Entityptr(new T());
        auto global = Entity::getGlobal();

        global->addOmni(novo->getName(), novo);
        global->addEurus( novo);
    }


    Entity(PlaceHolder) //Especial constructor
    {
    }
};

#define TO_STR(X) #X
template <class T>
class GenericEntity: public Entity
{
public:
    template <class ...D>
    GenericEntity(std::string name, D... t ) : Entity(t...), _name(name)
    {
    };


    std::string getName() const
    {
        return _name;
    }
    static PlaceHolder _instance;
    static_assert(&_instance);
    GenericEntity(PlaceHolder)
    {

    }
private:
    std::string _name;

} ;

template <class T>
Entity::PlaceHolder GenericEntity<T>::_instance = Entity::createGlobalEntity<T>();
//std::make_shared<GenericEntity<T>>(PlaceHolder());

class UniqueEntity :public Entity{
public:
    UniqueEntity(std::string name):_name(name){
    }
    std::string getName() const
    {
        return _name;
    }
private:
    std::string _name;
    static int _cont;


};

class JsonEntity : public Entity
{
public:
    JsonEntity(std::string _name,Json::Value val):_name(_name)
    {
        std::cerr<<"EurusSize:"<<_name<<" "<<_eurus.size()<<std::endl;

        for(auto& name: val.getMemberNames()) {
            Json::Value& subval = val[name];
            if(subval.isObject()) {
                std::cerr<<"Sub:"<<name<<std::endl;
                Entityptr toadd = Entityptr(new JsonEntity(name, subval));

                auto global = getGlobal();
                if( global->hasOmni(name) ) {
                    std::cerr<<"Adding "<<name<<std::endl;
                    auto current = global->getOmni(name);
                    current->extend(toadd);
                    global->addEurus(current);
                    addEurus(current);


                }else{
                    std::cerr<<"Creating "<<name<<std::endl;
                    global->addOmni(name,toadd);
                    global->addEurus(toadd);
                    addEurus(toadd);
                }

            } else {
                //  throw "foo";
            }

        }
    std::cerr<<"EurusSize:"<<_name<<" "<<_eurus.size()<<std::endl;


    }
    virtual std::string getName() const
    {
        return _name;
    }
    std::string _name;
};


struct ContextCreator {

    static Entityptr createFromJson(std::string file)
    {
        std::ifstream in(file);
        if(!in.is_open()) {
            throw "unable to open file";
        }
        Json::Value val;

        in>>val;
        Entityptr novo = Entityptr(new JsonEntity(file,val));

        return novo;
    }

};

}
