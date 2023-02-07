/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Pin
*/

#include <stdexcept>
#include "Pin.hpp"
#include "PinLink.hpp"
#include <iostream>

Pin::Pin(nts::IComponent &p, PinType t, size_t i):
    _type(t),
    _parent(p),
    _index(i)
{
}

Pin* Pin::getSource()
{
    if (_type == INPUT && !_links.empty()) {
        return _links[0].getOutput();
    }
    return nullptr;
}

nts::IComponent& Pin::getParent()
{
    return _parent;
}

nts::Tristate Pin::getValue()
{
    if (getPinType() == OUTPUT) {
        return _value;
    } else if (_links.size() == 0) {
        return nts::Undefined;
    } else {
        this->setValue(getSource()->getValue());
    }
    return _value;
}

Pin::PinType Pin::getPinType() const
{
    return _type;
}

void Pin::setValue(nts::Tristate new_val)
{
    _value = new_val;
}

void Pin::addLink(PinLink link)
{
    if (getPinType() == INPUT && !_links.empty()) {
        throw std::invalid_argument("Multi link to single input");
    }
    _links.push_back(link);
}
