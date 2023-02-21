/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/


#include "Output.hpp"
#include "Pin.hpp"
namespace nts::component::IO
{
    Output::Output()
    {
        addPin(1, Pin::INPUT);
    }

    nts::Tristate Output::getValue()
    {
        return (*this)[1].getValue();
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
