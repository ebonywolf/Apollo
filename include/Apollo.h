#ifndef APOLLO_H
#define APOLLO_H

#pragma once


#include "Entities/Entity.h"
#include "Entities/Process.h"
#include "Entities/Data.h"

using Particle  = std::shared_ptr<pg::Entity>;

#include "Templates/Templates.h"
#include "Entities/SpecialEntities.h"
#include "Entities/VariadicProcess.h"
#include "Entities/Data.h"
#include "Entities/GenericData.h"

#include "Entities/Basic.h"

template <class T, class ...Args>
std::shared_ptr<T> newParticle(Args...args){
    return std::make_shared<T>(args...);
}


std::string extern className(const std::string& prettyFunction);

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)





#endif
