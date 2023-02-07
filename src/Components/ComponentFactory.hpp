/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** ComponentFactory
*/

#pragma once
#include <memory>
#include "IComponent.hpp"

class ComponentFactory {
    public:

        static std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
};
