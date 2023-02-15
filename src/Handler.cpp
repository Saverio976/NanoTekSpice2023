/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "ComponentFactory.hpp"
#include "FileParser.hpp"
#include "Handler.hpp"
#include "IComponent.hpp"

namespace nts
{
    Handler::Handler():
        _shell(this)
    {
    }

    void Handler::readInput()
    {
        this->_shell.mainLoop();
    }

    void Handler::loadFile(const std::string &fileName)
    {
        FileParser file(fileName, this);
    }

    void Handler::addChipset(const std::string &type, const std::string &name)
    {
        std::map<std::string, std::string> choices = {
            {"input", "inputDisplay"},
            {"clock", "inputDisplay"},
            {"output", "outputDisplay"},
        };

        if (this->_components.find(name) != this->_components.end()) {
            throw ChipsetAlreadyCreatedException("Chipset: " + name + " already exists");
        }
        this->_components[name] = this->_componentFactory.createComponent(type);
        if (this->_specialComponents.find(type) == this->_specialComponents.end()) {
            this->_specialComponents[type] = {};
        }
        this->_specialComponents[type].push_back(name);
        if (choices.find(type) != choices.end()) {
            if (this->_specialComponents.find(choices[type]) == this->_specialComponents.end()) {
                this->_specialComponents[choices[type]] = {};
            }
            this->_specialComponents[choices[type]].push_back(name);
        }
    }

    void Handler::addLink(
        const std::string &name1,
        std::size_t pin1,
        const std::string &name2,
        std::size_t pin2
    )
    {
        if (this->_components.find(name1) == this->_components.end()) {
            throw ChipsetNameNotFoundException("Trying to link unkown component '" + name1 + "'");
        }
        if (this->_components.find(name2) == this->_components.end()) {
            throw ChipsetNameNotFoundException("Trying to link unkown component '" + name2 + "'");
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

    std::size_t Handler::getTick() const
    {
        return this->_tick;
    }

    const std::vector<std::string> &Handler::getChipsetNames(const std::string &type)
    {
        if (this->_specialComponents.find(type) == this->_specialComponents.end()) {
            throw ChipsetNameNotFoundException("Chipset type " + type + " not found");
        }
        return this->_specialComponents[type];
    }

    void Handler::incrementTick()
    {
        this->_tick += 1;
    }

    void Handler::syncChipsetTick()
    {
        for (auto &chipset : this->_components) {
            chipset.second->simulate(this->getTick());
        }
    }

    void Handler::checkGoodParsing() const
    {
        if (this->_components.empty()) {
            throw ChipsetNameNotFoundException("Circuit must contain at least 1 chipset");
        }
    }
}
