//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// Shell
//

#pragma once

#include <string>
#include "BaseError.hpp"

namespace nts
{
    class Handler;

    class Shell {
        public:
            class BadSetValueInput : public BaseError
            {
                using BaseError::BaseError;
            };

            class UnkownCommand: public BaseError
            {
                using BaseError::BaseError;
            };

            Shell(Handler *handler);
            ~Shell() = default;

            void mainLoop();
            static void setIsEndLoop(bool isEndLoop);

        private:
            bool _isEnd = false;
            Handler *_handler;

            std::string getInputName(const std::string &all) const;
            std::size_t getInputValue(const std::string &all) const;

            void setInput(const std::string &name, std::size_t value);
            void display() const;
            void simulate();
            void loop();
            void exit();
            void help() const;
            static bool _endLoop;
    };
}
