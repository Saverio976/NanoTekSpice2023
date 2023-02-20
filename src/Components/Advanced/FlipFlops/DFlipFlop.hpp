/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** DFlipFlop
*/

#pragma once
#include "AComponent.hpp"
#include <array>
#include "SoloGate.hpp"
#include "Inverter.hpp"
#include "Forker.hpp"
#include "SRFlipFlop.hpp"

namespace nts::component
{
    class DFlipFlop: public AComponent {
        public:
            DFlipFlop();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;

            Pin &operator [](size_t pin) override;
        private:
            SRFlipFlop _flipFlop;
            Inverter _not;
            std::array<Forker, 2> _forks;
            std::array<NandGate, 2> _nands;
    };
}
