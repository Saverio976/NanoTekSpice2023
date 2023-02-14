/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#include "Constants.hpp"
#include "IComponent.hpp"
#include "Pin.hpp"

namespace nts::component::IO
    {
    TrueInput::TrueInput()
    {
        _pins.push_back(Pin(*this, Pin::OUTPUT, 1));
        _pins[0].setValue(nts::True);
    }

    FalseInput::FalseInput()
    {
        _pins.push_back(Pin(*this, Pin::OUTPUT, 1));
        _pins[0].setValue(nts::False);
    }

    nts::Tristate TrueInput::compute(size_t pin)
    {
        if (pin != 1) {
            throw OutOfRange("True: chipset doesn't have enough pins");
        }
        return _pins[0].getValue();
    }

    nts::Tristate TrueInput::getValue()
    {
        return this->_pins[0].getValue();
    }

    nts::IComponent *TrueInput::clone() const
    {
        return new TrueInput();
    }

    nts::Tristate FalseInput::compute(size_t pin)
    {
        if (pin != 1) {
            throw OutOfRange("False: chipset doesn't have enough pins");
        }
        return _pins[0].getValue();
    }

    nts::IComponent *FalseInput::clone() const
    {
        return new FalseInput();
    }

    nts::Tristate FalseInput::getValue()
    {
        return this->_pins[0].getValue();
    }
}
