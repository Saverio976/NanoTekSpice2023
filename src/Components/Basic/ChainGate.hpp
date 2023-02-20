/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** ChainGate
*/

#pragma once
#include "AComponent.hpp"
#include "SoloGate.hpp"
#include <iostream>

namespace nts::component
{
    template <class T, std::size_t nbInput>
    class ChainGate: public AComponent {
        static_assert(std::is_base_of<SoloGate, T>::value, "ChainGate: template type must be derived from SoloGate");
        static_assert(nbInput >= 3, "ChainGate: template type requires at least 2 inputs");
        public:
            ChainGate()
            {
                for (size_t i = 0; i < nbInput - 2; i++) {
                    _gates[i].setLink(3, _gates[i + 1], 2);
                }
            }
            nts::Tristate compute(std::size_t pin) override
            {
                return (*this)[pin].getValue();
            }

            void simulate(std::size_t tick) override
            {
                if (_lastTick == tick) {
                    return;
                }
                _lastTick = tick;
                for (size_t i = 0; i < nbInput - 1; i++) {
                    _gates[i].simulate(tick);
                }
            }

            inline nts::IComponent *clone() const override {return new ChainGate<T, nbInput>;}

            Pin &operator [](std::size_t pin) override
            {
                if (pin == 0 || pin >= nbInput + 2) {
                    throw OutOfRange("QuadGate, Chipset doesn't have enough pins for pin n°" + std::to_string(pin) + ".");
                } else if (pin <= 2) {
                    return _gates[0][pin];
                } else if (pin == nbInput + 1) {
                    return _gates[nbInput - 2][3];
                } else {
                    return _gates[pin - 2][1];
                }
            }
        private:
            std::array<T, nbInput - 1> _gates;
    };
}
