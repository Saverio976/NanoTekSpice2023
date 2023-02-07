/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Pin
*/

#pragma once
#include "IComponent.hpp"
#include "PinLink.hpp"

class IPin
{
   public:
        enum PinType {
            INPUT,
            OUTPUT
        };

        virtual nts::Tristate getValue() = 0;
        virtual PinType getPinType() const = 0;

    protected:
        virtual void setValue(nts::Tristate) = 0;

    private:
};
