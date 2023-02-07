/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AndGate
*/

#include "AndGate.hpp"
#include "Pin.hpp"
#include "PinLink.hpp"
#include <iostream>

AndGate::AndGate()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::INPUT, 0));
    _pins.push_back(Pin(*this, Pin::INPUT, 1));
    _pins.push_back(Pin(*this, Pin::OUTPUT, 2));
}

static nts::Tristate tristate_and(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::False || b == nts::False) {
        return nts::False;
    } else if (a == nts::True && b == nts::True) {
        return nts::True;
    } else {
        return nts::Undefined;
    }
}

nts::Tristate AndGate::compute(std::size_t pin)
{
    if (pin > 3) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    if (pin < 2) {
        if (_pins[pin].getSource() != nullptr) {
            _pins[pin].getSource()->getParent().simulate(_lastTick);
        }
        return _pins[pin].getValue();
    }
    return tristate_and(_pins[0].getValue(), _pins[1].getValue());
}
