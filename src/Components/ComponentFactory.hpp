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

namespace nts
{
    class ComponentFactory {
        public:
            class TypeNotInFactory : public std::exception {
                public:
                    TypeNotInFactory(const std::string &type);
                    const char *what() const noexcept override;

                protected:
                    std::string _error;
            };
            ComponentFactory();

            void registerComponent(const std::string &type, nts::IComponent *component);
            void removeComponent(const std::string &type);

            std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
}
