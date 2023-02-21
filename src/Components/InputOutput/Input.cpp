/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Input
*/

#include "Input.hpp"
#include "IComponent.hpp"
#include "Pin.hpp"
namespace nts::component::IO
{
    Input::Input()
    {
        addPin(1, Pin::OUTPUT);
    }

    void Input::setValue(nts::Tristate new_val)
    {
        _value = new_val;
    }

    nts::Tristate Input::compute(std::size_t pin)
    {
        (*this)[pin].setValue(_value);
        return (*this)[pin].getValue();
    }

    nts::Tristate Input::getValue()
    {
        return (*this)[1].getValue();
    }

    nts::IComponent *Input::clone() const
    {
        return new Input();
    }
}
