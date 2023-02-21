/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Inverter
*/

#include "IComponent.hpp"
#include "Pin.hpp"
#include "Inverter.hpp"

namespace nts::component {
    Inverter::Inverter()
    {
        addPin(1, Pin::INPUT);
        addPin(2, Pin::OUTPUT);
    }

    static nts::Tristate triNot(nts::Tristate v)
    {
        if (v == nts::Undefined) {
            return nts::Undefined;
        } else if (v == nts::False) {
            return nts::True;
        } else {
            return nts::False;
        }
    }

    Tristate Inverter::compute(std::size_t pin)
    {
        if (pin == 1) {
            return (*this)[1].getValue();
        } else if (pin == 2) {
            (*this)[1].simulate(_lastTick);
            return triNot((*this)[1].getValue());
        }
        throw OutOfRange("Inverter: Chipset doesn't have enough pins");
    }

    IComponent *Inverter::clone() const
    {
        return new Inverter();
    }
}
