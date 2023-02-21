/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AndGate
*/

#include "SoloGate.hpp"
#include "IComponent.hpp"
#include "Pin.hpp"
#include "PinLink.hpp"

namespace nts::component {
    SoloGate::SoloGate()
    {
        addPin(1, Pin::INPUT);
        addPin(2, Pin::INPUT);
        addPin(3, Pin::OUTPUT);
    }

    void SoloGate::QuickLink(Pin *i1, Pin *i2)
    {
        setLink(&(*this)[1], i1);
        setLink(&(*this)[2], i2);
    }

    nts::Tristate SoloGate::compute(std::size_t pin)
    {
        if (pin == 3) {
            return operation((*this)[1].getValue(), (*this)[2].getValue());
        } else {
            (*this)[pin].simulate(_lastTick);
            return (*this)[pin].getValue();
        }
    }

    nts::IComponent *AndGate::clone() const
    {
        return new AndGate();
    }

    nts::Tristate AndGate::operation(nts::Tristate left, nts::Tristate right)
    {
        if (left == nts::False || right == nts::False) {
            return nts::False;
        } else if (left == nts::True && right == nts::True) {
            return nts::True;
        } else {
            return nts::Undefined;
        }
    }

    nts::IComponent *OrGate::clone() const
    {
        return new OrGate();
    }

    nts::Tristate OrGate::operation(nts::Tristate left, nts::Tristate right)
    {
        if (left == nts::True || right == nts::True) {
            return nts::True;
        } else if (left == nts::False && right == nts::False) {
            return nts::False;
        } else {
            return nts::Undefined;
        }
    }

    nts::IComponent *XorGate::clone() const
    {
        return new XorGate();
    }

    nts::Tristate XorGate::operation(nts::Tristate left, nts::Tristate right)
    {
        if (left == nts::Undefined || right == nts::Undefined) {
            return nts::Undefined;
        } else if (left != right) {
            return nts::True;
        } else {
            return nts::False;
        }
    }

    nts::IComponent *NorGate::clone() const
    {
        return new NorGate();
    }

    nts::Tristate NorGate::operation(nts::Tristate left, nts::Tristate right)
    {
        if (left == nts::True || right == nts::True) {
            return nts::False;
        } else if (left == nts::Undefined || right == nts::Undefined) {
            return nts::Undefined;
        } else {
            return nts::True;
        }
    }

    nts::IComponent *NandGate::clone() const
    {
        return new NandGate();
    }

    nts::Tristate NandGate::operation(nts::Tristate left, nts::Tristate right)
    {
        if (left == nts::False || right == nts::False) {
            return nts::True;
        } else if (left == nts::Undefined || right == nts::Undefined) {
            return nts::Undefined;
        } else {
            return nts::False;
        }
    }
}
