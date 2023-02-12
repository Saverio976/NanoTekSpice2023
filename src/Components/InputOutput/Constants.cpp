/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#include "Constants.hpp"
#include "IComponent.hpp"
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

nts::Tristate True::getValue()
{
    return this->_pins[0].getValue();
}

nts::IComponent *True::clone() const
{
    return new True();
}

nts::Tristate False::compute(size_t pin)
{
    if (pin != 1) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    return _pins[0].getValue();
}

nts::IComponent *False::clone() const
{
    return new False();
}

nts::Tristate False::getValue()
{
    return this->_pins[0].getValue();
}
