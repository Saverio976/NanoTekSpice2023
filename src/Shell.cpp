//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// Shell
//

#include <algorithm>
#include <cstddef>
#include <csignal>
#include <map>
#include <sstream>
#include <stdexcept>
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

namespace nts
{
    bool Shell::_endLoop = false;

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
            throw BadSetValueInput("Input value must be 0 or 1 or U but it was [" + valueStr + "]");
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
            } else if (line == "loop") {
                this->loop();
            } else if (line == "help") {
                this->help();
            } else {
                throw UnkownCommand("Unknown command [" + line + "]. Try help to have a list of commands");
            }
            std::cout << "> ";
        }
    }

    void Shell::setInput(const std::string &name, std::size_t value)
    {
        std::stringstream linestream;
        nts::IComponent *icomp = this->_handler->getChipset(name);
        component::IO::Input *iinput = dynamic_cast<component::IO::Input *>(icomp);
        std::map<std::size_t, nts::Tristate> choices = {
            {0, nts::False},
            {1, nts::True},
            {2, nts::Undefined},
        };

        if (iinput == nullptr) {
            linestream << value << " not an Input";
            throw BadSetValueInput("Can't set value of " + name + ", is not an input.");
        }
        iinput->setValue(choices[value]);
    }

    static void displayType(const std::string &type, Handler *handler)
    {
        std::vector<std::string> chipsets;
        component::IO::IIOComponent *iiocomponent = nullptr;

        try {
            chipsets = handler->getChipsetNames(type);
        } catch (const std::exception &e) {
            chipsets = {};
        }

        std::sort(chipsets.begin(), chipsets.end());

        for (const auto &i : chipsets) {
            iiocomponent = dynamic_cast<component::IO::IIOComponent *>(handler->getChipset(i));
            if (iiocomponent!= nullptr) {
                std::cout << "  " << i << ": " << iiocomponent->getValue() << std::endl;
            }
        }
    }

    void Shell::display() const
    {
        std::cout << "tick: " << this->_handler->getTick() << std::endl;
        std::cout << "input(s):" << std::endl;
        displayType("inputDisplay", this->_handler);
        std::cout << "output(s):" << std::endl;
        displayType("outputDisplay", this->_handler);
    }

    void Shell::simulate()
    {
        std::vector<std::string> chipsets = this->_handler->getChipsetNames("output");
        component::IO::Output *output = nullptr;

        this->_handler->incrementTick();
        for (auto &i : chipsets) {
            output = dynamic_cast<component::IO::Output *>(this->_handler->getChipset(i));
            if (output!= nullptr) {
                output->simulate(this->_handler->getTick());
            }
        }
        this->_handler->syncChipsetTick();
    }

    void Shell::setIsEndLoop(bool isEndLoop)
    {
        Shell::_endLoop = isEndLoop;
    }

    static void signal_handler(__attribute__((unused)) int _)
    {
        Shell::setIsEndLoop(true);
    }

    void Shell::loop()
    {
        std::signal(SIGINT, signal_handler);
        this->setIsEndLoop(false);
        while (Shell::_endLoop == false) {
            this->simulate();
            this->display();
        }
        std::signal(SIGINT, SIG_DFL);
    }

    void Shell::exit()
    {
        this->_isEnd = true;
    }

    void Shell::help() const
    {
        std::cout << "List of commands:" << std::endl;
        std::cout << "\t\033[1mhelp:\033[0m\t\tDisplays commands and what they do." << std::endl << std::endl;
        std::cout << "\t\033[1mdisplay:\033[0m\tDisplays the current tick, input(s) value(s) and output(s) value(s)." << std::endl << std::endl;
        std::cout << "\t\033[1msimulate:\033[0m\tUpdates the circuit and advances the ticks" << std::endl << std::endl;
        std::cout << "\t\033[1mloop:\033[0m\t\tContinuously calls simulate and display until (CTRL+C) is pressed." << std::endl << std::endl;
        std::cout << "\t\033[1mexit:\033[0m\t\tExits the program, same as (CTRL+D)." << std::endl << std::endl;
        std::cout << "\t\033[1m[in]=[0|1|U]:\033[0m\tChanges the value of the input component named in to false, true or undefined respectively." << std::endl;
        std::cout << "\t\t\tNote that to update the changes, you need to call simulate." << std::endl;
        std::cout << "\t\t\tOnly works in input and clock components, throws an error if used on anything else" << std::endl;
    }
}
