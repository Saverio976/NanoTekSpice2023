/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** SRFlipFlop
*/

#pragma once
#include <array>
#include "AComponent.hpp"
#include "SoloGate.hpp"
#include "Forker.hpp"

namespace nts::component
{
    class SRFlipFlop: public AComponent {
        public:
            SRFlipFlop();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;

            Pin &operator [](size_t pin) override;
        private:
            std::array<NandGate, 2> _nands;
    };
}
