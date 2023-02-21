/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** JKFlipFlop
*/

#include "JKFlipFlop.hpp"

namespace nts::component
{
    JKFlipFlop::JKFlipFlop()
    {
        _nands[0].setLink(2, _flipFlop, 4);
        _nands[0].setLink(3, _clockFork, 2);

        _nands[1].setLink(2, _flipFlop, 3);
        _nands[1].setLink(3, _clockFork, 2);

        _flipFlop.setLink(1, _nands[0], 4);
        _flipFlop.setLink(2, _nands[1], 4);
    }

    nts::Tristate JKFlipFlop::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    void JKFlipFlop::simulate(std::size_t lastTick)
    {
        _lastTick = lastTick;
        _flipFlop.simulate(lastTick);
    }

    nts::IComponent* JKFlipFlop::clone() const
    {
        return new JKFlipFlop();
    }

    Pin& JKFlipFlop::operator [](size_t pin)
    {
        if (pin <= 0 || pin >= 6) {
        }
        switch (pin) {
            case 1:
                return _nands[0][1];
            case 2:
                return _clockFork[1];
            case 3:
                return _nands[1][1];
            case 4:
                return _flipFlop[3];
            case 5:
                return _flipFlop[4];
            default:
                throw Pin::BadPin("SRFlipFlop: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        }
    }
}
