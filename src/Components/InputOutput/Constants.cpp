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
        addPin(1, Pin::OUTPUT);
        (*this)[1].setValue(nts::True);
    }

    FalseInput::FalseInput()
    {
        addPin(1, Pin::OUTPUT);
        (*this)[1].setValue(nts::False);
    }

    nts::IComponent *TrueInput::clone() const
    {
        return new TrueInput();
    }

    nts::IComponent *FalseInput::clone() const
    {
        return new FalseInput();
    }
}
