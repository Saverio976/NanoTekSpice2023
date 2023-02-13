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
    class TrueInput: public IIOComponent {
        public:
            TrueInput();
            nts::Tristate compute(size_t pin) override;

            nts::Tristate getValue() override;

            nts::IComponent *clone() const final;
    };

    class FalseInput: public IIOComponent {
        public:
            FalseInput();
            nts::Tristate compute(size_t pin) override;

            nts::Tristate getValue() override;

            nts::IComponent *clone() const final;
    };
}
