/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Clock
*/

#pragma once
#include "Input.hpp"

class Clock: public Input {
    public:
        void simulate(std::size_t tick) override;
};
