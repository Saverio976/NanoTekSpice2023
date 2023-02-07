/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AndGate
*/

#pragma once
#include "AComponent.hpp"
#include <iostream>

class AndGate: public AComponent {
    public:
        AndGate();
        nts::Tristate compute(std::size_t pin) override;
    protected:
    private:
};

