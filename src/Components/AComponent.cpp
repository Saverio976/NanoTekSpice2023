/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include <iostream>
#include "Pin.hpp"
#include "PinLink.hpp"


namespace nts
{
    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        PinLink link(nullptr, nullptr);
        nts::Pin *in;
        nts::Pin *out;

        if ((*this)[pin].getPinType() == other[otherPin].getPinType())
        {
            throw std::invalid_argument("Trying to link two pins of same type");
        }
        if ((*this)[pin].getPinType() == Pin::INPUT) {
            in = &(*this)[pin];
            out = &other[otherPin];
        } else {
            in = &other[otherPin];
            out = &(*this)[pin];
        }
        link = PinLink(in, out);
        in->addLink(link);
        out->addLink(link);
    }

    nts::Pin& AComponent::operator [](std::size_t index)
    {
        if (index == 0) {
            throw std::invalid_argument("Invalid pin");
        }
        if (index - 1 >= _pins.size()) {
            throw std::out_of_range("Chipset doesn't have enough pins");
        }
        return _pins[index - 1];
    }

    void AComponent::simulate(std::size_t tick)
    {
        if (_lastTick == tick) {
            return;
        }
        _lastTick = tick;
        for (size_t i = 0; i < _pins.size(); i++) {
            _pins[i].setValue(this->compute(i + 1));
        }
    }
}

std::ostream & operator <<(std::ostream &os, nts::Tristate val)
{
    if (val == nts::True) {
        os << "1";
    } else if (val == nts::False) {
        os << "0";
    } else {
        os << "U";
    }
    return os;
}
