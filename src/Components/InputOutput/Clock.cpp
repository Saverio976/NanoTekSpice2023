/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Clock
*/

#include "Clock.hpp"
#include "Pin.hpp"

void Clock::simulate(std::size_t tick)
{
    if (_value != nts::Undefined) {
        _value = (nts::Tristate)!_value;
    }
    AComponent::simulate(tick);
}
