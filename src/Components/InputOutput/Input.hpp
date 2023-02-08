/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AMutable
*/

#pragma once
#include "AComponent.hpp"

class Input: public AComponent {
    public:
        Input();
        void setValue(nts::Tristate);
        nts::Tristate compute(std::size_t pin) override;

    protected:
        nts::Tristate _value = nts::Undefined;

};
