/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Input
*/

#include "Input.hpp"
#include "Pin.hpp"

Input::Input()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::OUTPUT, 0));
}

void Input::setValue(nts::Tristate new_val)
{
    _value = new_val;
}

nts::Tristate Input::compute(std::size_t pin)
{
    if (pin != 0) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    _pins[0].setValue(_value);
    return _pins[0].getValue();
}
