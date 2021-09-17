#pragma once

#include <cstddef>

namespace ECS {
    using Entity = size_t;
    const Entity MAX_ENTITIES = 1000;
    const Entity INVALID_ENTITY = MAX_ENTITIES + 1;
}