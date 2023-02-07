/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Pin
*/

#pragma once

/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Pin
*/

#pragma once
#include <vector>
#include "IComponent.hpp"
#include "PinLink.hpp"

class Pin
{
    public:
        enum PinType {
            INPUT,
            OUTPUT,
            BRIDGE
        };

        Pin(nts::IComponent &, PinType, size_t);

        Pin *getSource();
        nts::IComponent &getParent();
        nts::Tristate getValue();
        PinType getPinType() const;
        void setValue(nts::Tristate);
        void addLink(PinLink link);

    private:
        const PinType _type;
        nts::IComponent &_parent;
        const size_t _index;
        nts::Tristate _value = nts::Undefined;
        std::vector<PinLink> _links;
};
