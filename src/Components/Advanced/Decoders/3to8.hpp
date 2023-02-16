/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** 2to4
*/

#pragma once
#include <array>
#include "AComponent.hpp"
#include "SoloGate.hpp"
#include "Inverter.hpp"
#include "Forker.hpp"
#include "Constants.hpp"
#include "2to4.hpp"

namespace nts::component
{
    class Decoder3to8: public AComponent
    {
        public:
            Decoder3to8();

            nts::IComponent *clone() const final;
            void simulate(std::size_t lastTick) override;

            Pin &operator [](size_t pin) override;
        private:
            Inverter _not;
            std::array<Decoder2to4, 2> _decoders;
            std::array<AndGate, 2> _filters;
            std::array<Forker, 4> _forks;
            IO::TrueInput t;
            IO::FalseInput f;
    };
}
