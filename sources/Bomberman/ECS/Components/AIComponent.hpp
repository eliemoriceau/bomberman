#pragma once

#include <queue>
#include "Vector3.hpp"
#include "Timer.hpp"

namespace ECS {
    struct AIComponent {
        std::shared_ptr<Raylib::Vector3> _target;
        std::shared_ptr<int> _attack;
        std::shared_ptr<int> _fley;
        std::shared_ptr<int> _bombDrop;
        std::shared_ptr<int> _up;
        std::shared_ptr<int> _down;
        std::shared_ptr<int> _left;
        std::shared_ptr<int> _right;
        std::shared_ptr<Timer> timer;
        std::shared_ptr<std::deque<std::shared_ptr<Raylib::Vector3>>> _nextTarget;
    };
}