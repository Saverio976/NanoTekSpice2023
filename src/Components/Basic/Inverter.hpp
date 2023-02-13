/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Inverter
*/

#pragma once
#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

namespace nts
{
    class Inverter: public AComponent {
        public:
            Inverter();
            nts::Tristate compute(std::size_t pin) override;

            nts::IComponent *clone() const final;
    };
}
