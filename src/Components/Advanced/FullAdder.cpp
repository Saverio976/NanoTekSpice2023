/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** FullAdder
*/

#include "FullAdder.hpp"
#include "Pin.hpp"

static nts::Pin *getOutput(nts::component::SoloGate &g)
{
    return &(g[3]);
}

namespace nts::component
{
    FullAdder::FullAdder()
    {
        Pin *a = &_forkers[0][2];
        Pin *b = &_forkers[1][2];
        Pin *c = &_forkers[2][2];

        _abAnd.QuickLink(a, b);
        _bcAnd.QuickLink(b, c);
        _acAnd.QuickLink(a, c);

        _inXor.QuickLink(a, b);
        _sumXor.QuickLink(getOutput(_inXor), c);

        _inOr.QuickLink(getOutput(_abAnd), getOutput(_bcAnd));
        _carryOr.QuickLink(getOutput(_inOr), getOutput(_acAnd));
    }

    nts::Tristate FullAdder::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    void FullAdder::simulate(std::size_t lastTick)
    {
        if (_lastTick == lastTick) {
            return;
        }
        _lastTick = lastTick;
        (*this)[4].setValue(this->compute(4));
        (*this)[5].setValue(this->compute(5));
    }

    nts::IComponent* FullAdder::clone() const
    {
        return new FullAdder;
    }

    Pin& FullAdder::operator [](size_t pin)
    {
        if (pin == 0) {
            throw Pin::BadPin("Default component: bad pin, can't access pin n°" + std::to_string(pin) + ".");
        } else if (pin >= 1 && pin <= 3) {
            return _forkers[pin - 1][1];
        } else if (pin == 4) {
            return _sumXor[3];
        } else if (pin == 5) {
            return _carryOr[3];
        } else {
            throw OutOfRange("FullAdder: chipset doesn't have enough pins to access pin n°" + std::to_string(pin) + ".");
        }
    }
}
