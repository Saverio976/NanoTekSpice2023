/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/


#include "Output.hpp"
namespace nts::component::IO
{
    Output::Output()
    {
        _pins.push_back(Pin(*this, Pin::INPUT, 1));
    }

    nts::Tristate Output::getValue()
    {
        return _pins[0].getValue();
    }

    nts::Tristate Output::compute(std::size_t pin)
    {
        (*this)[pin].simulate(_lastTick);
        return (*this)[pin].getValue();
    }

    nts::IComponent *Output::clone() const
    {
        return new Output();
    }
}
