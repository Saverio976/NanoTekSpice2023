/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#pragma once
#include <vector>
#include <ostream>
#include "IComponent.hpp"

class Pin;

class AComponent: public nts::IComponent {
    public:
        AComponent();
        ~AComponent();

        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        IComponent & operator [](std::size_t index);
        IComponent operator [](std::size_t index) const;
    private:
        std::vector<Pin> _pins;
        std::size_t _lastTick;
};

std::ostream & operator <<(std::ostream &os, nts::Tristate val);
