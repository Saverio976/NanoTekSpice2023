/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** SoloGate
*/

#pragma once
#include "Pin.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts::component
{
    class SoloGate: public AComponent {
        public:
            SoloGate();
            nts::Tristate compute(std::size_t pin) override;

        protected:
        private:
            virtual nts::Tristate operation(nts::Tristate left, nts::Tristate right) = 0;
    };

    class AndGate: public SoloGate
    {
        public:
            nts::IComponent *clone() const final;
        private:
            nts::Tristate operation(nts::Tristate left, nts::Tristate right) override;
    };

    class OrGate: public SoloGate
    {
        public:
            nts::IComponent *clone() const final;
        private:
            nts::Tristate operation(nts::Tristate left, nts::Tristate right) override;
    };

    class XorGate: public SoloGate
    {
        public:
            nts::IComponent *clone() const final;
        private:
            nts::Tristate operation(nts::Tristate left, nts::Tristate right) override;
    };

    class NorGate: public SoloGate
    {
        public:
            nts::IComponent *clone() const final;
        private:
            nts::Tristate operation(nts::Tristate left, nts::Tristate right) override;
    };

    class NandGate: public SoloGate
    {
        public:
            nts::IComponent *clone() const final;
        private:
            nts::Tristate operation(nts::Tristate left, nts::Tristate right) override;
    };
}
