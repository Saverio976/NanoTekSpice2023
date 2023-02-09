/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#pragma once
#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

class True: public AComponent {
    public:
        True();
        nts::Tristate compute(size_t pin) override;

        nts::IComponent *clone() const final;
};

class False: public AComponent {
    public:
        False();
        nts::Tristate compute(size_t pin) override;

        nts::IComponent *clone() const final;
};

