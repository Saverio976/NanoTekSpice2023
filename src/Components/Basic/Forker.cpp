/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Forker
*/

#include "Forker.hpp"
#include "Pin.hpp"

namespace nts::component
{
    Forker::Forker()
    {
        addPin(1, Pin::INPUT);
        addPin(2, Pin::OUTPUT);
    }

    nts::Tristate Forker::compute(std::size_t pin)
    {
        if (pin == 1) {
            (*this)[1].simulate(_lastTick);
            return (*this)[1].getValue();
        } else if (pin == 2) {
            return (*this)[1].getValue();
        }
        return (*this)[pin].getValue();
    }

    nts::IComponent* Forker::clone() const
    {
        return new Forker();
    }
}
