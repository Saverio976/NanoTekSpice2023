/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** DFlipFlop
*/

#include "DFlipFlop.hpp"

namespace nts::component
{
    DFlipFlop::DFlipFlop()
    {
        _not.setLink(1, _forks[0], 2);

        _nands[0].QuickLink(&_forks[0][2], &_forks[1][2]);
        _nands[1].QuickLink(&_not[2], &_forks[1][2]);

        _flipFlop.setLink(1, _nands[0], 3);
        _flipFlop.setLink(2, _nands[1], 3);
    }

    nts::Tristate DFlipFlop::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    void DFlipFlop::simulate(std::size_t tick)
    {
        _lastTick = tick;
        _flipFlop.simulate(tick);
    }

    nts::IComponent* DFlipFlop::clone() const
    {
        return new DFlipFlop();
    }

    Pin& DFlipFlop::operator [](size_t pin)
    {
        if (pin <= 0 || pin >= 5) {
            throw Pin::BadPin("DFlipFlop: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 2) {
            return _forks[pin - 1][1];
        } else {
            return _flipFlop[pin];
        }
    }
}
