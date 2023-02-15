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
        _pins.push_back(Pin(*this, Pin::INPUT, 1));
        _pins.push_back(Pin(*this, Pin::OUTPUT, 2));
    }

    nts::Tristate Forker::compute(std::size_t pin)
    {
        if (pin == 1) {
            _pins[0].simulate(_lastTick);
            return _pins[0].getValue();
        } else if (pin == 2) {
            return _pins[0].getValue();
        } else {
            throw OutOfRange("Forker only has 2 pins but tried to access n°" + std::to_string(pin) + ".");
        }
    }

    nts::IComponent* Forker::clone() const
    {
        return new Forker();
    }
}
