#pragma once

#include <list>
#include "Entity.hpp"

namespace ECS {
    class System {
    public:
        std::list<ECS::Entity> _entities{};
    };
}