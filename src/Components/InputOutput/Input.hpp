/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AMutable
*/

#pragma once
#include "IComponent.hpp"
#include "IIOComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"
namespace nts
{
    class Input: public IIOComponent {
        public:
            Input();
            void setValue(nts::Tristate);
            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate getValue() override;

            nts::IComponent *clone() const override;

        protected:
            nts::Tristate _value = nts::Undefined;
    };
}
