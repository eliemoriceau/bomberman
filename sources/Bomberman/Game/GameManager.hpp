//
// Created by marin on 11/06/2021.
//

#pragma once

#include <memory>
#include <vector>

template<typename T>
class GameManager {
public:
    void registerSystem(T system) {
        _systems.push_back(system);
    }

private:
    std::vector<T> _systems;
};