/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#pragma once
//This file and class will need a rename
#include <exception>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "IComponent.hpp"
#include "PinLink.hpp"

class Handler
{
    public:
        void loadFile(const std::string &fileName);
        void readInput();

        void addChipset(const std::string &type, const std::string &name);
        void addLink(const std::string &name1, std::size_t pin1,
                      const std::string &name2, std::size_t pin2);

    protected:
    private:
        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
        std::vector<PinLink> _links;
        std::size_t _tick;

        void setInput(const std::string &name, std::size_t value);
        void display() const;
        void simulate();
        void loop();
        void exit() const;
};
