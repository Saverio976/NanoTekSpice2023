/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Decoder4to16
*/

#include "4to16.hpp"

namespace nts::component
{
    Decoder4to16::Decoder4to16()
    {
        _not.setLink(1, _forks[3], 2);
        _filters[0].QuickLink(&_forks[4][2], &_not[2]);
        _filters[1].QuickLink(&_forks[4][2], &_forks[3][2]);

        _decoders[0].setLink(1, _forks[0], 2);
        _decoders[0].setLink(2, _forks[1], 2);
        _decoders[0].setLink(3, _forks[2], 2);
        _decoders[0].setLink(4, _filters[0], 3);

        _decoders[1].setLink(1, _forks[0], 2);
        _decoders[1].setLink(2, _forks[1], 2);
        _decoders[1].setLink(3, _forks[2], 2);
        _decoders[1].setLink(4, _filters[1], 3);
    }

    nts::IComponent* Decoder4to16::clone() const
    {
        return new Decoder4to16();
    }

    void Decoder4to16::simulate(std::size_t tick)
    {
        if (tick == _lastTick) {
            return;
        }
        _lastTick = tick;
        for (int i = 6; i < 36; i++) {
            (*this)[i].setValue(compute(i));
        }
    }

    Pin& Decoder4to16::operator [](size_t pin)
    {
        if (pin == 0 || pin >= 28) {
            throw Pin::BadPin("Decoder 4to16: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 5) {
            return _forks[pin - 1][1];
        } else if (pin >= 6 && pin <= 13) {
            return _decoders[0][pin - 1];
        } else {
            return _decoders[1][pin - 9];
        }
    }
}
