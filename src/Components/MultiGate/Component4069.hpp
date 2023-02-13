/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** SexaInverters
*/

#pragma once
#include "AComponent.hpp"
#include "Inverter.hpp"
#include <array>

namespace nts
{
    class Component4069: public AComponent {
        public:
            Component4069() = default;
            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;
            nts::IComponent *clone() const;
            Pin &operator [](std::size_t pin) override;

        private:
            std::array<Inverter, 6> _inverters;
    };
}
