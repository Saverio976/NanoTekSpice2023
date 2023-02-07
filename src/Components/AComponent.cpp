/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "../Pin/Pin.hpp"

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

void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    PinLink link(nullptr, nullptr);
    Pin *in;
    Pin *out;

    if (_pins[pin].getPinType() == other[otherPin].getPinType())
    {
        throw std::invalid_argument("Trying to link two pins of same type");
    }
    if (_pins[pin].getPinType() == Pin::INPUT) {
        in = &_pins[pin];
        out = &other[otherPin];
    } else {
        in = &other[otherPin];
        out = &_pins[pin];
    }
    link = PinLink(in, out);
    in->addLink(link);
    out->addLink(link);
}

const Pin &AComponent::operator [](std::size_t index) const
{
    if (index >= _pins.size()) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    return _pins[index];
}

Pin& AComponent::operator [](std::size_t index)
{
    if (index >= _pins.size()) {
        throw std::out_of_range("Chipset doesn't have enough pins");
    }
    return _pins[index];
}

void AComponent::simulate(std::size_t tick)
{
    nts::Tristate v;
    if (_lastTick == tick) {
        return;
    }
    _lastTick = tick;
    for (size_t i = 0; i < _pins.size(); i++) {
        v = this->compute(i);
        _pins[i].setValue(v);
    }
}
