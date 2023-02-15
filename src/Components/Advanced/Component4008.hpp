/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Component4008
*/

#pragma once
#include <array>
#include "AComponent.hpp"
#include "FullAdder.hpp"

namespace nts::component
{
    class Component4008 : public AComponent {
        public:
            Component4008();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;

            Pin &operator [](size_t pin) override;
            std::array<FullAdder, 4> _adders;
        private:

    };
}
