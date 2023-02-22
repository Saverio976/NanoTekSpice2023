/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#pragma once
//This file and class will need a rename
#include <cstddef>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "ComponentFactory.hpp"
#include "IComponent.hpp"
#include "PinLink.hpp"
#include "Shell.hpp"
#include "BaseError.hpp"
#include "Circuit.hpp"

namespace nts
{
    class Handler
    {
        public:
            Handler();

            void loadFile(const std::string &fileName);
            void checkGoodParsing() const;
            void readInput();

            std::size_t getTick() const;
            void incrementTick();
            void syncChipsetTick();

            Circuit &getCircuit();

        protected:
        private:
            std::size_t _tick = 0;
            Shell _shell;
            Circuit _circuit;
    };
}
