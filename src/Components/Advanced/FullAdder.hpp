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

            nts::IComponent *clone() const final;
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
