/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** IComponent
*/

#pragma once
#include <cstddef>

namespace nts
{
    class Pin;

    enum Tristate
    {
        Undefined = (-true),
        True = true,
        False = false
    };
    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
        virtual void setLink(nts::Pin *p1, nts::Pin *p2) = 0;

        virtual IComponent *clone() const = 0;

        virtual Pin &operator [](std::size_t index) = 0;
    };
}

