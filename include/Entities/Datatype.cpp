#include "Datatype.h"
#include "KeySet.h"
#include <ostream>
namespace pg
{

bool operator==(const Datatypeptr me, const Datatypeptr notme)
{
    return me->equals(notme);
}

Datatypeptr operator+(const Datatypeptr me, const Datatypeptr notme)
{
    return me->junction(notme);
}



void Datatype::join( Datatypeptr other)
{

}

std::string Datatype::toString() const
{
    return getHashKey()->toString();
}
Datatypeptr Datatype::getFrom() const
{
    throw "todo";
}
Datatypeptr Datatype::getTo() const
{
    throw "todo";
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
