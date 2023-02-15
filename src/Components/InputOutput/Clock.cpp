/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Clock
*/

#include "Clock.hpp"
#include "IComponent.hpp"
#include "Pin.hpp"

namespace nts::component::IO
{
    void Clock::simulate(std::size_t tick)
    {
        if (this->_lastTick == tick) {
            return;
        }
        AComponent::simulate(tick);
        if (_value != nts::Undefined) {
            _value = (nts::Tristate)!_value;
        }
    }

    nts::IComponent *Clock::clone() const
    {
        return new Clock();
    }

    nts::Tristate Clock::getValue()
    {
        return this->_pins[0].getValue();
    }
}
