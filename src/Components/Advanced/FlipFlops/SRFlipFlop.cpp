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
        _nands[0].setLink(2, _nands[1], 3);
        _nands[1].setLink(2, _nands[0], 3);
    }

    nts::Tristate SRFlipFlop::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    void SRFlipFlop::simulate(std::size_t tick)
    {
        _lastTick = tick;
        _nands[0].simulate(tick);
        _nands[1].simulate(tick);
    }

    nts::IComponent* SRFlipFlop::clone() const
    {
        return new SRFlipFlop();
    }

    Pin& SRFlipFlop::operator [](size_t pin)
    {
        if (pin <= 0 || pin >= 5) {
            throw Pin::BadPin("SRFlipFlop: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 2) {
            return _nands[pin - 1][1];
        } else {
            return _nands[pin - 3][3];
        }
    }
}
