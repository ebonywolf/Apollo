#include "Datatype.h"
#include "KeySet.h"



namespace pg {

bool operator==(const Datatypeptr me, const Datatypeptr notme){
    return me->equals(notme);
}

Datatypeptr operator+(const Datatypeptr me, const Datatypeptr notme){
    return me->junction(notme);
}


const Datatypeptr Datatype::NULL_DATA = std::make_shared<Datatype>();

std::string Datatype::toString() const {
    return getHashKey()->toString();
}
Datatypeptr Datatype::getFrom() const {
    throw "todo";
}
Datatypeptr Datatype::getTo() const {
    throw "todo";
}


Datatypeptr Datatype::junction(Datatypeptr other) const {
    throw "todo";
}

}
