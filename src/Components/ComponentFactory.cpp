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
#include "Pin.hpp"
#include "Basic/SoloGate.hpp"
#include "Basic/Inverter.hpp"
#include "InputOutput/Input.hpp"
#include "InputOutput/Output.hpp"
#include "InputOutput/Constants.hpp"
#include "InputOutput/Clock.hpp"
#include "MultiGate/QuadGate.hpp"
#include "MultiGate/Component4069.hpp"

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
    this->registerComponent("and", new AndGate);
    this->registerComponent("or", new OrGate);
    this->registerComponent("xor", new XorGate);
    this->registerComponent("nor", new NorGate);
    this->registerComponent("nand", new NandGate);
    this->registerComponent("not", new Inverter);
    this->registerComponent("input", new Input);
    this->registerComponent("output", new Output);
    this->registerComponent("false", new False);
    this->registerComponent("true", new True);
    this->registerComponent("clock", new Clock);
    this->registerComponent("4001", new QuadGate<NorGate>);
    this->registerComponent("4011", new QuadGate<NandGate>);
    this->registerComponent("4030", new QuadGate<XorGate>);
    this->registerComponent("4069", new Component4069);
    this->registerComponent("4071", new QuadGate<OrGate>);
    // TODO: add all component that we know of
}

void ComponentFactory::registerComponent(
    const std::string &type,
    nts::IComponent *component)
{
    if (this->_components.find(type) == this->_components.end()) {
        this->_components.insert(std::make_pair(type, std::unique_ptr<nts::IComponent>()));
    }
    this->_components[type].reset(component);
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
