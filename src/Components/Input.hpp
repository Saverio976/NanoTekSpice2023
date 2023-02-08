/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Input
*/

#pragma once
#include "AComponent.hpp"
#include "Pin.hpp"


class Input: public AComponent {
    public:
        Input();

        void setValue(nts::Tristate);
        nts::Tristate compute(std::size_t pin) override;
    protected:
    private:
        nts::Tristate _value = nts::Undefined;
};
