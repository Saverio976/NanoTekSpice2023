/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AndGate
*/

#include "SoloGate.hpp"
#include "Pin.hpp"
#include <iostream>
#include "PinLink.hpp"


SoloGate::SoloGate()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::INPUT, 1));
    _pins.push_back(Pin(*this, Pin::INPUT, 2));
    _pins.push_back(Pin(*this, Pin::OUTPUT, 3));
}

nts::Tristate SoloGate::compute(std::size_t pin)
{
    if (pin == 3) {
        _pins[0].simulate(_lastTick);
        _pins[1].simulate(_lastTick);
        return operation(_pins[0].getValue(), _pins[1].getValue());
    }
    return (*this)[pin].getValue();
}

nts::Tristate AndGate::operation(nts::Tristate left, nts::Tristate right)
{
    if (left == nts::False || right == nts::False) {
        return nts::False;
    } else if (left == nts::True && right == nts::True) {
        return nts::True;
    } else {
        return nts::Undefined;
    }
}

nts::Tristate OrGate::operation(nts::Tristate left, nts::Tristate right)
{
    if (left == nts::True || right == nts::True) {
        return nts::True;
    } else if (left == nts::False && right == nts::False) {
        return nts::False;
    } else {
        return nts::Undefined;
    }
}

nts::Tristate XorGate::operation(nts::Tristate left, nts::Tristate right)
{
    if (left == nts::Undefined || right == nts::Undefined) {
        return nts::Undefined;
    } else if (left != right) {
        return nts::True;
    } else {
        return nts::False;
    }
}

nts::Tristate NorGate::operation(nts::Tristate left, nts::Tristate right)
{
    if (left == nts::True || right == nts::True) {
        return nts::False;
    } else if (left == nts::Undefined || right == nts::Undefined) {
        return nts::Undefined;
    } else {
        return nts::True;
    }
}

nts::Tristate NandGate::operation(nts::Tristate left, nts::Tristate right)
{
    if (left == nts::False || right == nts::False) {
        return nts::True;
    } else if (left == nts::Undefined || right == nts::Undefined) {
        return nts::Undefined;
    } else {
        return nts::False;
    }
}


