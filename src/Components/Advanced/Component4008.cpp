/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Component4008
*/

#include "Component4008.hpp"

namespace nts::component
{
    Component4008::Component4008()
    {
        for (int i = 0; i < 3; i++)
        {
            _adders[i].setLink(5, _adders[i + 1], 3);
        }
    }

    void Component4008::simulate(std::size_t lastTick)
    {
        if (lastTick == _lastTick) {
            return;
        }
        _lastTick = lastTick;
        (*this)[10].setValue(this->compute(10));
        (*this)[11].setValue(this->compute(11));
        (*this)[12].setValue(this->compute(12));
        (*this)[13].setValue(this->compute(13));
        (*this)[14].setValue(this->compute(14));
    }

    nts::IComponent* Component4008::clone() const
    {
        return new Component4008();
    }

    Pin& Component4008::operator [](size_t pin)
    {
        switch (pin)
        {
        case 6:
        case 7:
            return _adders[0][pin - 5];
        case 9:
            return _adders[0][3];
        case 2:
        case 3:
            return _adders[2][4 - pin];
        case 4:
        case 5:
            return _adders[1][pin - 3];
        case 1:
            return _adders[3][1];
        case 15:
            return _adders[3][2];
        case 10:
        case 11:
        case 12:
        case 13:
            return _adders[pin - 10][4];
        case 14:
            return _adders[3][5];
        default:
            throw Pin::BadPin("4008: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        }
    }
}
