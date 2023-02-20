/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "Pin.hpp"
#include "PinLink.hpp"

namespace nts::component
{
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

    nts::Pin& AComponent::operator [](std::size_t index)
    {
        if (index == 0) {
            throw Pin::BadPin("Default component: bad pin, can't access pin n°" + std::to_string(index) + ".");
        }
        if (index - 1 >= _pins.size()) {
            throw OutOfRange("Default component: chipset doesn't have enough pins to access pin n°" + std::to_string(index) + ".");
        }
        return _pins[index - 1];
    }

    void AComponent::simulate(std::size_t tick)
    {
        nts::Tristate oldValue;

        if (_lastTick == tick && !_hasChanged) {
            return;
        }
        _lastTick = tick;
        _hasChanged = false;
        for (size_t i = 0; i < _pins.size(); i++) {
            oldValue = _pins[i].getValue();
            _pins[i].setValue(this->compute(i + 1));
            if (oldValue != _pins[i].getValue() && _pins[i].getPinType() == Pin::INPUT) {
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
