//
// Created by marin on 09/06/2021.
//

#include <utility>
#include "Exception.hpp"

ECS::Exception::Exception(std::string message) : _message(std::move(message)) {
}

const char *ECS::Exception::what() {
    return (_message.c_str());
}