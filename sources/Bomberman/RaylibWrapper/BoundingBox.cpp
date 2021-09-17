/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "BoundingBox.hpp"

Raylib::BoundingBox::BoundingBox(Vector3 pos, Vector3 size) : _pos(pos), _size(size),
                                                              _min({_pos.x - _size.x / 2,
                                                                    _pos.y - _size.y / 2,
                                                                    _pos.z - _size.z / 2}),
                                                              _max({_pos.x + _size.x / 2,
                                                                    _pos.y + _size.y / 2,
                                                                    _pos.z + _size.z / 2}),
                                                              _box({_min, _max}) {
}

::BoundingBox Raylib::BoundingBox::getBox() const {
    return _box;
}
