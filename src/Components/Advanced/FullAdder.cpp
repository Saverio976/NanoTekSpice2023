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
        addPin(1, &_forkers[0][1]);
        addPin(2, &_forkers[1][1]);
        addPin(3, &_forkers[2][1]);
        addPin(4, &_sumXor[3]);
        addPin(5, &_carryOr[3]);

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

    nts::IComponent* FullAdder::clone() const
    {
        return new FullAdder;
    }
}
