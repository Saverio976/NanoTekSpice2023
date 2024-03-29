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
#include "BaseError.hpp"

namespace nts
{
    class Pin
    {
        public:
            enum PinType {
                INPUT,
                OUTPUT
            };


            class BadPin: public BaseError
            {
                using BaseError::BaseError;
            };

            Pin(nts::IComponent &, PinType, size_t);

            Pin *getSource();
            nts::IComponent &getParent();
            nts::Tristate getValue();
            PinType getPinType() const;
            void setValue(nts::Tristate);
            void addLink(PinLink link);
            void simulate(size_t tick);

        private:
            const PinType _type;
            nts::IComponent &_parent;
            const size_t _index;
            nts::Tristate _value = nts::Undefined;
            std::vector<PinLink> _links;
    };
}
