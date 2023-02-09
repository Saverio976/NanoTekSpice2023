/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/

#pragma once
#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

class Output: public AComponent {
    public:
        Output();

        nts::Tristate getValue();
        nts::Tristate compute(std::size_t pin) override;

        nts::IComponent *clone() const final;
};
