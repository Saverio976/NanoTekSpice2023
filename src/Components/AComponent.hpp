/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#pragma once
#include <map>
#include <ostream>
#include <list>
#include "IComponent.hpp"
#include "Pin.hpp"
#include "BaseError.hpp"

namespace nts::component
{
    class AComponent: public nts::IComponent {
        public:
            class OutOfRange: public BaseError
            {
                using BaseError::BaseError;
            };

            nts::Tristate compute(std::size_t pinIndex) override;
            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void setLink(nts::Pin *p1, nts::Pin *p2) override;


            nts::Pin &operator [](std::size_t index) override;
        protected:
            std::map<size_t, Pin *> _pinMap;
            std::list<Pin> _innerPins;
            bool _hasChanged;
            std::size_t _lastTick = 0;

            void addPin(std::size_t index, Pin::PinType type);
            void addPin(std::size_t index, Pin *pin);
    };
}

std::ostream & operator <<(std::ostream &os, nts::Tristate val);
