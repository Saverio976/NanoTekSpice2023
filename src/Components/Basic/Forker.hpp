/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Forker
*/

#pragma once
#include "AComponent.hpp"

namespace nts::component
{
    class Forker: public AComponent {
        public:
            Forker();

            nts::Tristate compute(std::size_t pin) override;
            nts::IComponent *clone() const final;
        private:
    };
}
