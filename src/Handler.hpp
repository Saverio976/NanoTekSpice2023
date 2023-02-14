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

namespace nts
{
    class Handler
    {
        public:
            class ChipsetAlreadyCreatedException : public BaseError
            {
                using BaseError::BaseError;
            };
            class ChipsetNameNotFoundException : public BaseError
            {
                using BaseError::BaseError;
            };

            Handler();

            void loadFile(const std::string &fileName);
            void checkGoodParsing() const;
            void readInput();

            std::size_t getTick() const;
            void incrementTick();
            void syncChipsetTick();

            void addChipset(const std::string &type, const std::string &name);
            void addLink(const std::string &name1, std::size_t pin1,
                        const std::string &name2, std::size_t pin2);

            nts::IComponent *getChipset(const std::string &name);
            const std::vector<std::string> &getChipsetNames(const std::string &type);

        protected:
        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
            std::map<std::string, std::vector<std::string>> _specialComponents;
            std::size_t _tick = 0;
            Shell _shell;
            component::ComponentFactory _componentFactory;
    };
}
