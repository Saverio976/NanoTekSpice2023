//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// Shell
//

#include <cstddef>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <regex>
#include "IComponent.hpp"
#include "IIOComponent.hpp"
#include "InputOutput/Input.hpp"
#include "InputOutput/Output.hpp"
#include "Handler.hpp"
#include "Shell.hpp"

Shell::BadSetValueInput::BadSetValueInput(const std::string &error):
    _error(error)
{
}

const char *Shell::BadSetValueInput::what() const noexcept
{
    return this->_error.data();
}

Shell::Shell(Handler *handler):
    _handler(handler)
{
}

std::string Shell::getInputName(const std::string &all) const
{
    std::string name;
    std::string rest;
    std::string intermediate;
    std::stringstream s;

    intermediate = std::regex_replace(all, std::regex("="), " ");
    s.str(intermediate);
    s >> name >> rest;
    return name;
}

std::size_t Shell::getInputValue(const std::string &all) const
{
    std::string name;
    std::string valueStr;
    int value = -1;
    std::stringstream s;
    std::string intermediate;

    intermediate = std::regex_replace(all, std::regex("="), " ");
    s.str(intermediate);
    s >> name >> valueStr;
    if (valueStr == "U") {
        return 2;
    }
    value = std::stoi(valueStr);
    if (value > 1 || value < 0) {
        throw BadSetValueInput("Value must be 0 or 1 or U");
    }
    return value;
}

void Shell::mainLoop()
{
    std::string line;

    std::cout << "> ";
    while (!this->_isEnd && std::getline(std::cin, line)) {
        if (line.find('=') != line.npos) {
            this->setInput(this->getInputName(line), this->getInputValue(line));
        } else if (line == "display") {
            this->display();
        } else if (line == "simulate") {
            this->simulate();
        } else if (line == "exit") {
            this->exit();
        }
        std::cout << "> ";
        // TODO: what to do if unknow command ?
    }
}

void Shell::setInput(const std::string &name, std::size_t value)
{
    std::stringstream linestream;
    nts::IComponent *icomp = this->_handler->getChipset(name);
    Input *iinput = dynamic_cast<Input *>(icomp);
    std::map<std::size_t, nts::Tristate> choices = {
        {0, nts::False},
        {1, nts::True},
        {2, nts::Undefined},
    };

    if (iinput == nullptr) {
        linestream << value << " not an Input";
        throw BadSetValueInput(linestream.str());
    }
    iinput->setValue(choices[value]);
}

void Shell::display() const
{
    std::vector<std::string> abc;
    IIOComponent *iiocomponent = nullptr;

    std::cout << "tick: " << this->_handler->getTick() << std::endl;
    abc = this->_handler->getChipsetNames("input");
    std::cout << "input(s):" << std::endl;
    for (const auto &i : abc) {
        iiocomponent = dynamic_cast<IIOComponent *>(this->_handler->getChipset(i));
        if (iiocomponent!= nullptr) {
            std::cout << "  " << i << ": " << iiocomponent->getValue() << std::endl;
        }
    }
    abc = this->_handler->getChipsetNames("output");
    std::cout << "output(s):" << std::endl;
    for (const auto &i : abc) {
        iiocomponent = dynamic_cast<IIOComponent *>(this->_handler->getChipset(i));
        if (iiocomponent!= nullptr) {
            std::cout << "  " << i << ": " << iiocomponent->getValue() << std::endl;
        }
    }
}

void Shell::simulate()
{
    std::vector<std::string> abc = this->_handler->getChipsetNames("output");
    Output *output = nullptr;

    this->_handler->incrementTick();
    for (auto &i : abc) {
        output = dynamic_cast<Output *>(this->_handler->getChipset(i));
        if (output!= nullptr) {
            output->simulate(this->_handler->getTick());
        }
    }
    this->_handler->syncChipsetTick();
}

void Shell::loop()
{
    // TODO:
}

void Shell::exit()
{
    this->_isEnd = true;
}
