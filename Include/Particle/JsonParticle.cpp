#include "JsonParticle.h"

namespace ap{

void JsonParticle::readFromFile(std::string file)
{
    std::ifstream in(file);
    if (!in.is_open()) {
        throw "unable to open file";
    }
    Json::Value val;

    in >> val;

    auto jsonEntity = pg::Entityptr(new pg::JsonEntity(file, val));
    Particle *alce = new ChargedParticle(jsonEntity);
    reset(alce);
}

}
