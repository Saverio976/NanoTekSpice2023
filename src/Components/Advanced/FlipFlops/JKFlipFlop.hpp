/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** JKFlipFlop
*/

#pragma once
#include <array>
#include "AComponent.hpp"
#include "Forker.hpp"
#include "SRFlipFlop.hpp"
#include "ChainGate.hpp"

namespace nts::component
{
    class JKFlipFlop: public AComponent {
        public:
            JKFlipFlop();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;

            Pin &operator [](size_t pin) override;
        private:
            SRFlipFlop _flipFlop;
            Forker _clockFork;
            std::array<ChainGate<NandGate, 3>, 2> _nands;
    };
}
