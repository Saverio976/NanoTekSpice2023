/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** 4040Counter
*/

#pragma once
#include <array>
#include <map>
#include "AComponent.hpp"
#include "Pin.hpp"

namespace nts::component
{
    class Component4040: public AComponent
    {
        public:
            Component4040();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t lastTick) override;
            nts::IComponent *clone() const final;
        private:
            size_t _counter = 0;
            size_t _lastIncrement = 0;
            static const std::map<size_t, size_t> _indexMap;

            void reset();
            void increment();
    };
}
