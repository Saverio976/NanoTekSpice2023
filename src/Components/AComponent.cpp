/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "Pin.hpp"
#include "PinLink.hpp"
#include <iostream>

namespace nts::component
{
    nts::Tristate AComponent::compute(std::size_t pinIndex)
    {
        (*this)[pinIndex].simulate(_lastTick);
        return (*this)[pinIndex].getValue();
    }

    void AComponent::setLink(nts::Pin *p1, nts::Pin *p2)
    {
        PinLink link(nullptr, nullptr);

        if (p1->getPinType() == p2->getPinType())
        {
            throw PinLink::InvalidLink("Trying to link two pins of same type");
        }

        if (p1->getPinType() == Pin::INPUT) {
            link = PinLink(p1, p2);
        } else {
            link = PinLink(p2, p1);
        }
        p1->addLink(link);
        p2->addLink(link);
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        setLink(&(*this)[pin], &other[otherPin]);
    }

    void AComponent::addPin(std::size_t index, Pin::PinType type)
    {
        _innerPins.emplace_back(Pin(*this, type, index));
        _pinMap.emplace(index, &_innerPins.back());
    }

    void AComponent::addPin(std::size_t index, Pin *pin)
    {
        _pinMap.emplace(index, pin);
    }

    nts::Pin& AComponent::operator [](std::size_t index)
    {
        if (!_pinMap.contains(index)) {
            throw Pin::BadPin("Bad pin, can't access pin n°" + std::to_string(index) + ".");
        } else {
            return *_pinMap[index];
        }
    }

    void AComponent::simulate(std::size_t tick)
    {
        nts::Tristate oldValue;

        if (_lastTick == tick) {
            return;
        }
        _lastTick = tick;
        _hasChanged = false;
        for (auto &[index, pin] : _pinMap) {
            oldValue = pin->getValue();
            pin->setValue(this->compute(index));
            if (pin->getPinType() == Pin::INPUT && oldValue != pin->getValue()) {
                _hasChanged = true;
            }
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
