#include "JsonParticle.h"

namespace ap{



JsonParticle::JsonParticle(std::string name):UnchargedParticle(readFromFile(name)){

}
pg::Entityptr JsonParticle::readFromFile(std::string file)
{
    std::ifstream in(file);
    if (!in.is_open()) {
        throw "unable to open file";
    }
    Json::Value val;

    in >> val;

    auto jsonEntity = pg::Entityptr(new pg::JsonEntity(file, val));
    return jsonEntity;

}

}
