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
#include "Shell.hpp"

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

    s.str(all.substr(all.find('=') + 1));
    s >> value;
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
