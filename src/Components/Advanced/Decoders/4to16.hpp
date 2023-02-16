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
#include "Forker.hpp"
#include "3to8.hpp"

namespace nts::component
{
    class Decoder4to16: public AComponent
    {
        public:
            Decoder4to16();

            nts::IComponent *clone() const final;
            void simulate(std::size_t lastTick) override;

            Pin &operator [](size_t pin) override;
        private:
            Inverter _not;
            std::array<Decoder3to8, 2> _decoders;
            std::array<AndGate, 2> _filters;
            std::array<Forker, 5> _forks;
    };
}
