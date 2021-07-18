#include "Datatype.h"
#include "Identification/KeySet.h"
#include <ostream>
#include "SpecialDataTypes/NullDataType.h"
#include "SpecialDataTypes/AllDataType.h"

namespace pg
{

decltype( std::bind(NullType::get) ) Null = std::bind(NullType::get);
decltype( std::bind(AllType::get) ) All = std::bind(AllType::get);

bool operator==(const Datatypeptr me, const Datatypeptr notme)
{
    return me->equals(notme);
}

const Datatypeptr Datatype::getNull(){
      return Null();
}



Datatypeptr operator+(const Datatypeptr me, const Datatypeptr notme)
{
    return me->junction(notme);
}



void Datatype::join(const Datatypeptr other)
{

    _key->join(other);
}

std::string Datatype::toString() const
{
    return getHashKey()->toString();
}

Datatypeptr Datatype::getFrom() const
{
   return pg::Null();
}

Datatypeptr Datatype::getTo() const
{
  return shared_from_this();
}
Datatypeptr Datatype::getHashKey() const
{
    return _key;
}
Datatypeptr Datatype::getInverseDataPair()const
{
    throw "todo";
}
Datatypeptr Datatype::getDataPair()const
{
    throw "todo";
}
Datatypeptr Datatype::junction(const Datatypeptr other) const
{
    std::shared_ptr<KeySet> keyset=std::make_shared<KeySet>();
    Datatypeptr alce = this->shared_from_this();
    keyset->join( alce );
    keyset->join(other);
    return keyset;
}

}

namespace std{
   std::string to_string(pg::Datatypeptr obj){
       return obj->toString();
   }
}


