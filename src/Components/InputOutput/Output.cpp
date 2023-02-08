/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/

#include "Output.hpp"

Output::Output()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::INPUT, 0));
}

nts::Tristate Output::getValue()
{
    return _pins[0].getValue();
}

nts::Tristate Output::compute(std::size_t pin)
{
    if (pin != 0) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    _pins[0].simulate(_lastTick);
    return _pins[0].getValue();
}
