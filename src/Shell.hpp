//
// EPITECH PROJECT, 2023
// nanotekspice
// File description:
// Shell
//

#pragma once

#include <string>
class Handler;

class Shell {
    public:
        Shell(Handler *handler);
        ~Shell() = default;

        void mainLoop();

    private:
        bool _isEnd = false;
        Handler *_handler;

        std::string getInputName(const std::string &all) const;
        std::size_t getInputValue(const std::string &all) const;

        void setInput(const std::string &name, std::size_t value);
        void display() const;
        void simulate();
        void loop();
        void exit() const;
};
