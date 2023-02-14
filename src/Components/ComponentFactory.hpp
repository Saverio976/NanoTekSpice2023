/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** ComponentFactory
*/

#pragma once
#include <map>
#include <memory>
#include <string>
#include "IComponent.hpp"
#include "BaseError.hpp"

namespace nts::component
{
    class ComponentFactory {
        public:
            class TypeNotInFactory : public BaseError
            {
                using BaseError::BaseError;
            };
            ComponentFactory();

            void registerComponent(const std::string &type, nts::IComponent *component);
            void removeComponent(const std::string &type);

            std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
}
