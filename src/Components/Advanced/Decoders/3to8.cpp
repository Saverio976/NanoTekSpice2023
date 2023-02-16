/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** *
*/

#include "3to8.hpp"

namespace nts::component
{
    Decoder3to8::Decoder3to8()
    {
        _not.setLink(1, _forks[2], 2);
        _filters[0].QuickLink(&_forks[3][2], &_not[2]);
        _filters[1].QuickLink(&_forks[3][2], &_forks[2][2]);

        _decoders[0].setLink(1, _forks[0], 2);
        _decoders[0].setLink(2, _forks[1], 2);
        _decoders[0].setLink(3, _filters[0], 3);

        _decoders[1].setLink(1, _forks[0], 2);
        _decoders[1].setLink(2, _forks[1], 2);
        _decoders[1].setLink(3, _filters[1], 3);
    }

    nts::IComponent* Decoder3to8::clone() const
    {
        return new Decoder3to8();
    }

    void Decoder3to8::simulate(std::size_t lastTick)
    {
        if (lastTick == _lastTick) {
            return;
        }
        _lastTick = lastTick;
        for (int i = 5; i < 8; i++) {
            (*this)[i].setValue(compute(i));
        }
    }

    Pin& Decoder3to8::operator [](size_t pin)
    {
        if (pin == 0 || pin >= 13) {
            throw Pin::BadPin("Decoder 3to8: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 4) {
            return _forks[pin - 1][1];
        } else if (pin >= 5 && pin <= 8) {
            return _decoders[0][pin - 1];
        } else {
            return _decoders[1][pin - 5];
        }
    }
}
