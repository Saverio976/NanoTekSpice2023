/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** OutputPin
*/

#pragma once
#include <vector>
#include "IPin.hpp"
#include "PinLink.hpp"

class OutputPin: public IPin {
    public:
        OutputPin();
        ~OutputPin();

    protected:
    private:
        const PinType _type;
        std::vector<PinLink *> _links;
};
