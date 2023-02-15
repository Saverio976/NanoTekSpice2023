/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Constants
*/

#pragma once
#include "IComponent.hpp"
#include "IIOComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"
namespace nts::component::IO
{
    class TrueInput: public AComponent {
        public:
            TrueInput();
            nts::Tristate compute(size_t pin) override;

            nts::IComponent *clone() const final;
    };

    class FalseInput: public AComponent {
        public:
            FalseInput();
            nts::Tristate compute(size_t pin) override;

            nts::IComponent *clone() const final;
    };
}
