/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/


#include <iostream>
#include "Output.hpp"

Output::Output()
{
    _lastTick = 0;
    _pins.push_back(Pin(*this, Pin::INPUT, 1));
}

nts::Tristate Output::getValue()
{
    return _pins[0].getValue();
}

nts::Tristate Output::compute(std::size_t pin)
{
    (*this)[pin].simulate(_lastTick);
    return (*this)[pin].getValue();
}
