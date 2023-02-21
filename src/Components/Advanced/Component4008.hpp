/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Component4008
*/

#pragma once
#include <array>
#include "AComponent.hpp"
#include "FullAdder.hpp"

namespace nts::component
{
    class Component4008 : public AComponent {
        public:
            Component4008();

            nts::IComponent *clone() const final;
        private:
            std::array<FullAdder, 4> _adders;

            void addInput();
            void addOutput();
    };
}
