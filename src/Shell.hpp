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
        class BadSetValueInput : public std::exception {
            public:
                BadSetValueInput(const std::string &error);
                const char *what() const noexcept override;

            protected:
                std::string _error;
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
        static bool _endLoop;
};
