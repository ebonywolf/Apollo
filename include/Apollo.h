#ifndef APOLLO_H
#define APOLLO_H

#pragma once

#include "Templates/Templates.h"
#include "Entities/SpecialEntities.h"
#include "Entities/Data.h"

std::string extern className(const std::string& prettyFunction);

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)









#endif
