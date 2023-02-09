/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AMutable
*/

#pragma once
#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

class Input: public AComponent {
    public:
        Input();
        void setValue(nts::Tristate);
        nts::Tristate compute(std::size_t pin) override;

        nts::IComponent *clone() const override;

    protected:
        nts::Tristate _value = nts::Undefined;

};
