/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Inverter
*/

#include "Pin.hpp"
#include "Inverter.hpp"

Inverter::Inverter()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::INPUT, 1));
    _pins.push_back(Pin(*this, Pin::OUTPUT, 2));
}

static nts::Tristate triNot(nts::Tristate v)
{
    if (v == nts::Undefined) {
        return nts::Undefined;
    } else if (v == nts::False) {
        return nts::True;
    } else {
        return nts::False;
    }
}

nts::Tristate Inverter::compute(std::size_t pin)
{
    if (pin == 0) {
        return _pins[0].getValue();
    } else if (pin == 1) {
        _pins[0].simulate(_lastTick);
        return triNot(_pins[1].getValue());
    }
    throw std::out_of_range("Chipset doesn't have enough pins");
}
