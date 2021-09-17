#pragma once

#include <bitset>

namespace ECS {
    using ComponentType = size_t;
    const ComponentType MAX_COMPONENTS = 20;
    using UID = std::bitset<MAX_COMPONENTS>;
}