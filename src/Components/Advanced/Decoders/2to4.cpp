/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** 2to4
*/

#include "2to4.hpp"
#include "Pin.hpp"

namespace nts::component
{
    Decoder2to4::Decoder2to4()
    {
        _forks[0].setLink(2, _nots[0], 1);
        _forks[1].setLink(2, _nots[1], 1);

        _ands[0].QuickLink(&_nots[0][2], &_nots[1][2]);
        _ands[1].QuickLink(&_forks[0][2], &_nots[1][2]);
        _ands[2].QuickLink(&_nots[0][2], &_forks[1][2]);
        _ands[3].QuickLink(&_forks[0][2], &_forks[1][2]);

        for (int i = 0; i < 4; i++) {
            _filters[i].QuickLink(&_forks[2][2], &_ands[i][3]);
        }
    }

    nts::IComponent* Decoder2to4::clone() const
    {
        return new Decoder2to4();
    }

    void Decoder2to4::simulate(std::size_t lastTick)
    {
        if (lastTick == _lastTick) {
            return;
        }
        _lastTick = lastTick;
        (*this)[3].setValue(this->compute(3));
        (*this)[4].setValue(this->compute(4));
        (*this)[5].setValue(this->compute(5));
        (*this)[6].setValue(this->compute(6));
    }

    Pin& Decoder2to4::operator [](size_t pin)
    {
        if (pin == 0 || pin >= 8) {
            throw Pin::BadPin("Decoder 2to4: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 3) {
            return _forks[pin - 1][1];
        } else {
            return _filters[pin - 4][3];
        }
    }
}
