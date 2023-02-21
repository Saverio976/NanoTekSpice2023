/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Component4008
*/

#include "Component4008.hpp"

namespace nts::component
{
    void Component4008::addInput()
    {
        addPin(7, &_adders[0][1]);
        addPin(6, &_adders[0][2]);
        addPin(9, &_adders[0][3]);

        addPin(5, &_adders[1][1]);
        addPin(4, &_adders[1][2]);

        addPin(3, &_adders[2][1]);
        addPin(2, &_adders[2][2]);

        addPin(1, &_adders[3][1]);
        addPin(15, &_adders[3][2]);
    }

    void Component4008::addOutput()
    {
        addPin(10, &_adders[0][4]);
        addPin(11, &_adders[1][4]);
        addPin(12, &_adders[2][4]);
        addPin(13, &_adders[3][4]);
        addPin(14, &_adders[3][5]);
    }

    Component4008::Component4008()
    {
        addInput();
        addOutput();
        for (int i = 0; i < 3; i++)
        {
            _adders[i].setLink(5, _adders[i + 1], 3);
        }
    }

    nts::IComponent* Component4008::clone() const
    {
        return new Component4008();
    }
}
