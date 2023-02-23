//
// EPITECH PROJECT, 2023
// nano
// File description:
// circuit
//

#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "IComponent.hpp"
#include "ComponentFactory.hpp"

#pragma once

namespace nts
{
    class Circuit
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

            Circuit() = default;
            void checkGoodParsing() const;
            void syncChipsetTick(std::size_t tick);

            void addChipset(const std::string &type, const std::string &name);
            void addLink(const std::string &name1, std::size_t pin1,
                        const std::string &name2, std::size_t pin2);

            nts::IComponent *getChipset(const std::string &name);
            const std::vector<std::string> &getChipsetNames(const std::string &type);
        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
            std::map<std::string, std::vector<std::string>> _specialComponents;
            component::ComponentFactory _componentFactory;
    };
}
