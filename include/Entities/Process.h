#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <fstream>
#include <functional>
#include <iostream>

#include <json/json.h>
#include "Data.h"
#include "EntityBase.h"
#include "Datatype.h"
#include "Packet.h"

namespace pg
{

class Entity;
class Process;
//using Processptr = std::shared_ptr<Process>;
class Process: public Process_Base
{ //Defines function
public:
    /*
    Process() :_key(std::make_shared<DataPair>())
    {
    }
    */
    Process(Datatypeptr key) :_key(key) {
    }
    Process(Datatypeptr from, Datatypeptr to) :
            _key(std::make_shared<DataPair>(from, to))
    {

    }

    virtual void handle(Entityptr ent, Packet d) =0;

    virtual Future send(Dataptr sentData, const Datatypeptr fromType,
            Processptr context)
    {
        throw "todo";
    }

    virtual void omniUpdate(const Processptr context)
    {
        throw "todo";
    }
    virtual void eurusUpdate(const Processptr context)
    {
        throw "todo";
    }
    virtual void warnEurusChange(const Processptr context)
    {
        throw "todo";
    }
    virtual void warnOmniChange(const Processptr context)
    {
        throw "todo";
    }
    virtual Processptr getOmni() const
    {
        throw "todo";
    }
    virtual Processptr getEurus() const
       {
           throw "todo";
       }

    /*
     virtual Processptr getNull() const  {
     return std::make_shared<Process>( HashKey::NULL,HashKey::NULL );
     }
     */

    virtual bool hasEurus(const Datatypeptr) const
    {
        throw "todo";
    }
    virtual bool hasOmni(const Datatypeptr name) const
    {
        throw "todo";
    }
    virtual Processptr getOmni(const Datatypeptr name) const
    {
        throw "todo";
    }

    virtual void extend(const Processptr other)
    {
        throw "todo";
    }
    virtual int size() const
    {
        return 1;
    }
    virtual void receiveData(const Processptr context, Packet packet);

    virtual std::string toString() const override
    {
        return _key->toString();
    }
    virtual Datatypeptr getFrom() const override
    {
        return _key->getFrom();
    }

    virtual bool contains(Datatypeptr d)const override
    {
        return _key->contains(d);
    }

    virtual Datatypeptr getTo() const override
    {
        return _key->getTo();
    }
    virtual Datatypeptr getHashKey() const override
    {
        return _key;
    }
    virtual Datatypeptr getInverseDataPair() const override
    {
        return _key->getInverseDataPair();
    }
    virtual Datatypeptr getDataPair() const override
    {
        return _key->getDataPair();
    }
    virtual Datatypeptr junction(Datatypeptr other) const override
    {
        throw "Todo";
    }

protected:
    Datatypeptr _key;

};

}

namespace std
{
template<>
struct hash<pg::Process>
{
    std::size_t operator()(const pg::Process &k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.getHashKey()->toString());

    }
};
}

namespace pg
{

/*

 template <class MY_TYPE>
 struct Singleton: public Object<MY_TYPE>
 {
 static std::shared_ptr<MY_TYPE> get( MY_TYPE* val=0  ){

 static std::shared_ptr<MY_TYPE> me;
 if(val){
 me.reset(val);
 }
 if(!me){
 me=std::make_shared<MY_TYPE>();
 }
 return me;
 }

 protected:
 Singleton(){}

 };

 template <class MY_TYPE>
 struct MultiInstance : public Object<MY_TYPE> {
 static std::shared_ptr<MY_TYPE> get(){
 //TODO guarantee cleanup
 return std::make_shared<MY_TYPE>();
 }
 };


 */

}

