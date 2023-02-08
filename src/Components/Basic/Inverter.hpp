/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Inverter
*/

#pragma once
#include "AComponent.hpp"

class Inverter: public AComponent {
    public:
        Inverter();
        nts::Tristate compute(std::size_t pin) override;
};
