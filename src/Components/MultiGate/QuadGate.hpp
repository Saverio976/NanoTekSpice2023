/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** QuadGate
*/

#pragma once
#include <array>
#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"
#include "SoloGate.hpp"

namespace nts::component
{
    template <class T>
    class QuadGate: public AComponent {
        static_assert(std::is_base_of<SoloGate, T>::value, "QuadGate: template type must be derived from SoloGate");
        public:
            QuadGate() {}
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
                for (int i = 0; i < 4; i++) {
                    _gates[i].simulate(tick);
                }
            }

            inline nts::IComponent *clone() const override {return new QuadGate<T>;}

            Pin &operator [](std::size_t pin) override
            {
                if (pin == 0 || pin == 7 || pin == 14) {
                    throw std::invalid_argument("Invalid pin");
                }
                switch (pin) {
                    case 1:
                    case 2:
                    case 3:
                        return _gates[0][pin];
                    case 8:
                    case 9:
                    case 10:
                        return _gates[2][pin - 7];

                    case 4:
                        return _gates[1][3];
                    case 5:
                        return _gates[1][1];
                    case 6:
                        return _gates[1][2];

                    case 11:
                        return _gates[3][3];
                    case 12:
                        return _gates[3][1];
                    case 13:
                        return _gates[3][2];
                    default:
                        throw std::out_of_range("Chipset doesn't have enough pins");
                }
            }
        private:
            std::array<T, 4> _gates;
    };
}
