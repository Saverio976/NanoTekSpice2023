/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#pragma once
#include "IComponent.hpp"
#include "IIOComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

class True: public IIOComponent {
    public:
        True();
        nts::Tristate compute(size_t pin) override;

        nts::Tristate getValue() override;

        nts::IComponent *clone() const final;
};

class False: public IIOComponent {
    public:
        False();
        nts::Tristate compute(size_t pin) override;

        nts::Tristate getValue() override;

        nts::IComponent *clone() const final;
};

