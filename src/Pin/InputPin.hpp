/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** InputPin
*/

#pragma once
#include "IPin.hpp"
#include "PinLink.hpp"

class InputPin: public IPin {
    public:
        InputPin();
        ~InputPin();

    protected:
    private:
        const PinType _type;
        PinLink *_link;
};
