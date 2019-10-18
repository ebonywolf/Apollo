#include "Entity.h"


namespace pg{


std::size_t EntityptrHash::operator()(const pg::Entityptr& k) const
{
    return std::hash<std::string>()(k->getName());
}

}
