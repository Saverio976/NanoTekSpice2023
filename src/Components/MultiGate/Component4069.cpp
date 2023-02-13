/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Component4069
*/

#include <iostream>
#include "Pin.hpp"
#include "Component4069.hpp"

namespace nts::component
{
    nts::Tristate Component4069::compute(std::size_t pin)
    {
        return (*this)[pin].getValue();
    }

    void Component4069::simulate(std::size_t tick)
    {
        if (_lastTick == tick) {
            return;
        }
        _lastTick = tick;
        for (int i = 0; i < 6; i++) {
            _inverters[i].simulate(tick);
        }
    }

    nts::IComponent *Component4069::clone() const
    {
        return new Component4069;
    }

    Pin &Component4069::operator [](std::size_t pin)
    {
        size_t offset = 0;

        if (pin > 14) {
            throw std::out_of_range("4069: Chipset doesn't have enough pins");
        }
        if (pin == 0 || pin == 7 || pin == 14) {
            throw std::invalid_argument("Invalid pin");
        }
        offset = (pin > 7) ? 2 : 1;
        return _inverters[(pin - offset) / 2][(pin - 1) % 2 + 1];
    }
}
