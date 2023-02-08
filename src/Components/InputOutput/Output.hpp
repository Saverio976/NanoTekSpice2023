/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/

#pragma once
#include "AComponent.hpp"
#include "Pin.hpp"


class Output: public AComponent {
    public:
        Output();

        nts::Tristate getValue();
        nts::Tristate compute(std::size_t pin) override;
};
