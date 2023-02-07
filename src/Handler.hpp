/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#pragma once
//This file and class will need a rename
#include "IComponent.hpp"
#include "PinLink.hpp"
#include <vector>
#include <map>
#include <string>

class Handler
{
    public:
        void load_file(const std::string &file_name);
        void read_input();

    protected:
    private:
        std::map<std::string, nts::IComponent> _components;
        std::vector<PinLink> _links;
        std::size_t _tick;

        void add_chipset(const std::string &type, const std::string &name);
        void add_link(const std::string &name_1, std::size_t pin_1,
                      const std::string &name_2, std::size_t pin_2);

        void set_input(const std::string &name, std::size_t value);
        void display() const;
        void simulate();
        void loop();
        void exit() const;
};
