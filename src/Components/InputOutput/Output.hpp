/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Output
*/

#pragma once
#include "IComponent.hpp"
#include "IIOComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

namespace nts::component::IO
{
    class Output: public IIOComponent {
        public:
            Output();

            nts::Tristate getValue() override;
            nts::Tristate compute(std::size_t pin) override;

            nts::IComponent *clone() const final;
    };
}
