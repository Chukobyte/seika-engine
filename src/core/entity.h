#ifndef ENTITY_H
#define ENTITY_H

#include "component/component.h"

using Entity = std::uint32_t;

using ComponentSignature = std::bitset<MAX_COMPONENT_TYPES>;

const Entity MAX_ENTITIES = 20000;

const Entity INVALID_ENTITY = 0;

#endif //ENTITY_H