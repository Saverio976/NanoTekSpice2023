/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** 2to4
*/

#pragma once
#include "AComponent.hpp"
#include <array>
#include "SoloGate.hpp"
#include "Inverter.hpp"
#include "Forker.hpp"

namespace nts::component
{
    class Decoder2to4: public AComponent
    {
        public:
            Decoder2to4();

            nts::IComponent *clone() const final;
            void simulate(std::size_t lastTick) override;

            Pin &operator [](size_t pin) override;
        private:
            std::array<AndGate, 4> _ands;
            std::array<Inverter, 2> _nots;
            std::array<Forker, 3> _forks;
            std::array<AndGate, 4> _filters;
    };
}
