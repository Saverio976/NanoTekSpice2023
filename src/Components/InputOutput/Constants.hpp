/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#pragma once
#include "AComponent.hpp"

class True: public AComponent {
    public:
        True();
        nts::Tristate compute(size_t pin) override;
};

class False: public AComponent {
    public:
        False();
        nts::Tristate compute(size_t pin) override;
};

