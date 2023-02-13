/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Clock
*/

#pragma once
#include "IComponent.hpp"
#include "Input.hpp"

namespace nts
{
    class Clock: public Input {
        public:
            void simulate(std::size_t tick) override;

            nts::Tristate getValue() override;

            nts::IComponent *clone() const final;
    };
}
