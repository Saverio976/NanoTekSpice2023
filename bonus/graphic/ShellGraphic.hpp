//
// EPITECH PROJECT, 2023
// nano
// File description:
// graphical implementation
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include "Shell.hpp"
#include "PositionGate.hpp"

class ShellGraphic: public nts::Shell
{
    public:
        ShellGraphic(nts::Handler *handler);

        void mainLoop() override;
    private:
        sf::RenderWindow _window;

        void drawGate(const std::string &name, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color = sf::Color::Magenta);
        void drawGatesLinks(PositionGate &gate);
        void draw();

        void initInputs();
        void initOutputs();
        void initOtherGates();
        void initInputBox();

        std::vector<std::string> _outputsType = {"output"};
        std::vector<std::string> _inputsType = {"input", "clock", "true", "false"};
        std::vector<PositionGate> _gates;
        int _size_x = 20;
        int _size_y = 20;
        int _padding_middle = 5;
        int _padding_extern = 10;

        sf::Font _font;

        std::string _inputBoxString = "";
        sf::Text _inputBoxText;
        sf::RectangleShape _inputBox;
};
