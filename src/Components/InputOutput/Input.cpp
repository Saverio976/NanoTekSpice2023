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
        _lastTick = 0;
        _pins.push_back(Pin(*this, Pin::OUTPUT, 1));
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
        return this->_pins[0].getValue();
    }

    nts::IComponent *Input::clone() const
    {
        return new Input();
    }
}
