/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include "IComponent.hpp"
#include "BaseError.hpp"

namespace nts::component
{
    class AComponent: public nts::IComponent {
        public:
            class OutOfRange: public BaseError
            {
                using BaseError::BaseError;
            };

            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void setLink(nts::Pin *p1, nts::Pin *p2) override;


            nts::Pin &operator [](std::size_t index) override;
        protected:
            std::vector<Pin> _pins;
            std::size_t _lastTick = 0;
    };
}

std::ostream & operator <<(std::ostream &os, nts::Tristate val);
