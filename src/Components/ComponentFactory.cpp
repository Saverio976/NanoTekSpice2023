//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// ComponentFactory
//

#include <memory>
#include <string>
#include "ComponentFactory.hpp"
#include "IComponent.hpp"

ComponentFactory::TypeNotInFactory::TypeNotInFactory(const std::string &error):
    _error(error)
{
}

const char *ComponentFactory::TypeNotInFactory::what() const noexcept
{
    return this->_error.data();
}

ComponentFactory::ComponentFactory()
{
    // TODO: add all component that we know of
}

void ComponentFactory::registerComponent(
    const std::string &type,
    std::unique_ptr<nts::IComponent> component)
{
    if (this->_components.find(type) == this->_components.end()) {
        this->_components.insert(std::make_pair(type, std::unique_ptr<nts::IComponent>()));
    }
    this->_components[type].swap(component);
}

void ComponentFactory::removeComponent(const std::string &type)
{
    this->_components.erase(type);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &type)
{
    std::unique_ptr<nts::IComponent> newComp;

    if (this->_components.find(type) == this->_components.end()) {
        throw TypeNotInFactory(type);
    }
    newComp.reset(this->_components[type]->clone());
    return newComp;
}
