//
// Created by marin on 09/06/2021.
//

#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <cstring>

namespace ECS {

    class Exception : public std::exception {
    public:
        explicit Exception(std::string message);

        ~Exception() override = default;

        const char *what();

    private:
        std::string _message;
    };
}
