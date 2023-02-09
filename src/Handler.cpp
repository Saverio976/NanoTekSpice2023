/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include "ComponentFactory.hpp"
#include "FileParser.hpp"
#include "Handler.hpp"
#include "IComponent.hpp"

Handler::Handler():
    _shell(this)
{
}

void Handler::readInput()
{
    this->_shell.mainLoop();
}

Handler::ChipsetAlreadyCreatedException::ChipsetAlreadyCreatedException(const std::string &error):
    _error(error)
{
}

const char *Handler::ChipsetAlreadyCreatedException::what() const noexcept
{
    return this->_error.data();
}

Handler::ChipsetNameNotFoundException::ChipsetNameNotFoundException(const std::string &error):
    _error(error)
{
}

const char *Handler::ChipsetNameNotFoundException::what() const noexcept
{
    return this->_error.data();
}

void Handler::loadFile(const std::string &fileName)
{
    FileParser file(fileName, this);
}

void Handler::addChipset(const std::string &type, const std::string &name)
{
    if (this->_components.find(name) != this->_components.end()) {
        throw ChipsetAlreadyCreatedException("Chipset: " + name);
    }
    this->_components[name] = this->_componentFactory.createComponent(type);
    if (this->_specialComponents.find(type) == this->_specialComponents.end()) {
        this->_specialComponents[type] = {};
    }
    this->_specialComponents[type].push_back(name);
}

void Handler::addLink(
    const std::string &name1,
    std::size_t pin1,
    const std::string &name2,
    std::size_t pin2
)
{
    if (this->_components.find(name1) == this->_components.end() ||
        this->_components.find(name2) == this->_components.end()
    ) {
        throw ChipsetNameNotFoundException("Chipset: " + name1 + " or " + name2);
    }
    this->_components[name1]->setLink(pin1, *this->_components[name2].get(), pin2);
}

nts::IComponent *Handler::getChipset(const std::string &name)
{
    if (this->_components.find(name) == this->_components.end()) {
        return nullptr;
    }
    return this->_components[name].get();
}
