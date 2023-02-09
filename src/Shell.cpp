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
#include "IComponent.hpp"
#include "InputOutput/Input.hpp"
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

    name = all.substr(0, all.find('='));
    return name;
}

std::size_t Shell::getInputValue(const std::string &all) const
{
    std::size_t value;
    std::stringstream s;
    std::string strVal;

    s.str(all.substr(all.find('=') + 1));
    s >> strVal;
    if (strVal == "U") {
        return 2;
    }
    s.exceptions(std::ios::failbit);
    s >> value;
    if (value > 1) {
        throw BadSetValueInput("Value must be 0 or 1 or U");
    }
    return value;
}

void Shell::mainLoop()
{
    std::string line;

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
    // TODO:
}

void Shell::simulate()
{
    // TODO:
}

void Shell::loop()
{
    // TODO:
}

void Shell::exit()
{
    this->_isEnd = true;
}
