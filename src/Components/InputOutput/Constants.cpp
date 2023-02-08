/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#include "Constants.hpp"
#include "Pin.hpp"

True::True()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::OUTPUT, 1));
    _pins[0].setValue(nts::True);
}

False::False()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::OUTPUT, 1));
    _pins[0].setValue(nts::False);
}

nts::Tristate True::compute(size_t pin)
{
    if (pin != 1) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    return _pins[0].getValue();
}

nts::Tristate False::compute(size_t pin)
{
    if (pin != 1) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    return _pins[0].getValue();
}
