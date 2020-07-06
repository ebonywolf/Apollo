#ifndef APOLLO_H
#define APOLLO_H

#pragma once

#include "Entity/Entity.h"
#include "Entity/UniqueEntity.h"
#include "Process/Process.h"
#include "DataType/Data.h"

using Particle  = std::shared_ptr<pg::Entity>;


#include "Process/VariadicProcess.h"
#include "DataType/Data.h"
#include "DataType/GenericData.h"

#include "SpecialEntities/Basic.h"

template <class T, class ...Args>
std::shared_ptr<T> newParticle(Args...args){
    return std::make_shared<T>(args...);
}


std::string extern className(const std::string& prettyFunction);

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)





#endif
