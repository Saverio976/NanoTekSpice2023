/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** FullAdder
*/

#pragma once
#include "AComponent.hpp"
#include "Forker.hpp"
#include "SoloGate.hpp"
#include <array>

namespace nts::component
{
    class FullAdder : public AComponent {
        public:
            FullAdder();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;

            Pin &operator [](size_t pin) override;
        private:
            std::array<Forker, 3> _forkers;
            AndGate _abAnd;
            AndGate _bcAnd;
            AndGate _acAnd;

            XorGate _inXor;
            XorGate _sumXor;

            OrGate _inOr;
            OrGate _carryOr;

    };
}
