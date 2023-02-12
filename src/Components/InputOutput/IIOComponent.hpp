//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// IIOComponent
//

#pragma once

#include "IComponent.hpp"
#include "Pin.hpp"
#include "AComponent.hpp"

class IIOComponent : public AComponent {
    public:
        virtual nts::Tristate getValue() = 0;
};
