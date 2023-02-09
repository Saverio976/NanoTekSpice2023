/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** PinLink
*/

#include "PinLink.hpp"

PinLink::PinLink(Pin *in, Pin *out)
{
    _input = in;
    _output = out;
}

PinLink::~PinLink()
{
}

Pin* PinLink::getOutput()
{
    return _output;
}

Pin* PinLink::getInput()
{
    return _input;
}
