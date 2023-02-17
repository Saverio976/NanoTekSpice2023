/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** SRFlipFlop
*/

#include "SRFlipFlop.hpp"
#include "Pin.hpp"
#include <iostream>

namespace nts::component
{
    SRFlipFlop::SRFlipFlop()
    {
        _pins.push_back(Pin(*this, Pin::OUTPUT, 3));
        _pins.push_back(Pin(*this, Pin::OUTPUT, 4));

        this->setLink(3, _nands[1], 2);
        this->setLink(4, _nands[0], 2);
    }

    nts::Tristate SRFlipFlop::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    void SRFlipFlop::simulate(std::size_t tick)
    {
        if (_lastTick == tick) {
            return;
        }
        _lastTick = tick;
        (*this)[3].setValue(_nands[0][3].getValue());
        (*this)[4].setValue(_nands[1][3].getValue());
        _nands[0].simulate(_lastTick);
        _nands[1].simulate(_lastTick);
    }

    nts::IComponent* SRFlipFlop::clone() const
    {
        return new SRFlipFlop();
    }

    Pin& SRFlipFlop::operator [](size_t pin)
    {
        if (pin <= 0 || pin >= 5) {
            throw Pin::BadPin("4008: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 2) {
            return _nands[pin - 1][1];
        } else {
            return _pins[pin - 3];
        }
    }
}
