
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace pg{


template<typename T>
struct enable_shared_from_this_virtual;

class enable_shared_from_this_virtual_base : public std::enable_shared_from_this<enable_shared_from_this_virtual_base>
{
    typedef std::enable_shared_from_this<enable_shared_from_this_virtual_base> base_type;
    template<typename T>
    friend struct enable_shared_from_this_virtual;

    std::shared_ptr<enable_shared_from_this_virtual_base> shared_from_this()
    {
        return base_type::shared_from_this();
    }
    std::shared_ptr<enable_shared_from_this_virtual_base const> shared_from_this() const
    {
        return base_type::shared_from_this();
    }
};

template<typename T>
struct enable_shared_from_this_virtual: virtual enable_shared_from_this_virtual_base {
    typedef enable_shared_from_this_virtual_base base_type;

public:
    std::shared_ptr<T> shared_from_this()
    {
        std::shared_ptr<T> result(base_type::shared_from_this(), static_cast<T*>(this));
        return result;
    }

    std::shared_ptr<T const> shared_from_this() const
    {
        std::shared_ptr<T const> result(base_type::shared_from_this(), static_cast<T const*>(this));
        return result;
    }
};


class Process_Base;
class Entity_Base;
using Processptr = std::shared_ptr<Process_Base>;
using Entityptr = std::shared_ptr<Entity_Base>;
using C_Entityptr = std::shared_ptr<const Entity_Base>;

class Packet;
class EntitySet;
class ProcessSet;
class DataPair;


struct Process_Base : public enable_shared_from_this_virtual<Process_Base>{

    virtual Dataptr handle(Entityptr ent, Dataptr d) const =0;
    virtual Future send(Dataptr sentData, const Datatype fromType, Processptr context )=0;

    virtual std::string getHashKey()const = 0;

    virtual void omniUpdate(const Processptr context) = 0;
    virtual void eurusUpdate(const Processptr context) = 0;

    virtual void warnEurusChange(Processptr context) = 0;
    virtual void warnOmniChange(Processptr context) = 0;

    virtual ProcessSet getOmniList() const = 0;


    virtual bool hasEurus(DataPair) const=0;
    virtual void receiveData(Processptr context, Packet packet)=0;
};


template <class T>
Entityptr cast(T ptr){
    return std::dynamic_pointer_cast<Entity_Base>(ptr);
}
struct Entity_Base : public Process_Base {


    virtual void addOmni(const Processptr obj) = 0;
    virtual void addEurus( const Processptr obj) = 0;
    virtual void extend(Processptr other) = 0;

    virtual bool hasOmni(std::string name) const =0;
    virtual Processptr getOmni(std::string name) const = 0;

    virtual void update() =0;

};





struct EntityptrHash{
    std::size_t operator()(const pg::Entityptr& k) const;
};

struct Entitycmp
{
  bool operator() (const Entityptr& t1, const Entityptr& t2) const;
};


struct EntitySet: public std::unordered_set<Entityptr,EntityptrHash,Entitycmp>
{
    bool contains(std::string name) const;
    bool contains(DataPair) const;
    void insert(Processptr ){

    }
    Entityptr get(std::string name) const;
};

struct ProcessptrHash{
    std::size_t operator()(const pg::Processptr& k) const;
};

struct Processcmp
{
  bool operator() (const Processptr& t1, const Processptr& t2) const;
};

struct ProcessSet: public std::unordered_set<Processptr,ProcessptrHash,Processcmp>
{
    bool contains(std::string name) const;
    bool contains(DataPair) const;
    Processptr get(std::string name) const;
};



struct EntityMap : public std::unordered_map<DataPair,Entityptr> {
    using  std::unordered_map<DataPair,Entityptr>::unordered_map;

    Entityptr& operator()(const Datatype& from,const Datatype& to)
    {
        DataPair par (from,to);
        return operator [] (par);
    }
    const  Entityptr& operator()(const Datatype& from,const Datatype& to) const
    {
        DataPair par (from,to);
        if(!count(par))throw "foo";
        return at(par);
    }
};


}
