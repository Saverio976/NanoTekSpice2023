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
        virtual PinType getPinType() = 0;

    private:
};
