//
// EPITECH PROJECT, 2023
// nano
// File description:
// shell in graphics mode
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <algorithm>
#include <vector>
#include "ComponentFactory.hpp"
#include "ShellGraphic.hpp"
#include "Shell.hpp"
#include "Handler.hpp"

ShellGraphic::ShellGraphic(nts::Handler *handler):
    Shell(handler),
    _window(sf::VideoMode(800, 600), "NanoTekSpice", sf::Style::Close)
{
    this->_window.setVerticalSyncEnabled(true);
}

void ShellGraphic::mainLoop()
{
    while (this->_isEnd == false && this->_window.isOpen()) {
        this->draw();
        sf::Event event;
        while (this->_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->_window.close();
            }
        }
    }
}

void ShellGraphic::draw()
{
    this->_window.clear(sf::Color::Black);
    this->drawOtherGates();
    this->drawInputs();
    this->drawOutputs();
    this->_window.display();
}

void ShellGraphic::drawInputs()
{
    sf::Vector2f pos(0 + this->_padding_extern, 0 + this->_padding_extern);
    sf::Vector2f size(this->_size_x, this->_size_y);

    for (auto &type : this->_inputsType) {
        std::vector<std::string> components;
        try {
            components = this->_handler->getCircuit().getChipsetNames(type);
        } catch (...) {
            continue;
        }
        for (auto &input : components) {
            this->drawGate(input, pos, size);
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::drawOutputs()
{
    sf::Vector2f pos(
        this->_window.getSize().x - this->_padding_extern - this->_size_x,
        this->_padding_extern
    );
    sf::Vector2f size(this->_size_x, this->_size_y);

    for (auto &type : this->_outputsType) {
        std::vector<std::string> components;
        try {
            components = this->_handler->getCircuit().getChipsetNames(type);
        } catch (...) {
            continue;
        }
        for (auto &output : components) {
            this->drawGate(output, pos, size);
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::drawOtherGates()
{
    nts::component::ComponentFactory componentFactory;
    sf::Vector2f pos(
        (this->_window.getSize().x / 2.0) - (this->_size_x / 2.0),
        0 + this->_padding_extern
    );
    sf::Vector2f size(this->_size_x, this->_size_y);

    for (auto &type : componentFactory.getComponentTypes()) {
        std::vector<std::string> components;
        if (std::find(this->_inputsType.begin(), this->_inputsType.end(), type) != this->_inputsType.end()) {
            continue;
        }
        if (std::find(this->_outputsType.begin(), this->_outputsType.end(), type) != this->_inputsType.end()) {
            continue;
        }
        try {
            components = this->_handler->getCircuit().getChipsetNames(type);
        } catch (...) {
            continue;
        }
        for (auto &component : components) {
            this->drawGate(component, pos, size);
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::drawGate(const std::string &name, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color)
{
    auto component = this->_handler->getCircuit().getChipset(name);
    sf::RectangleShape rect(size);

    if (component == nullptr) {
        return;
    }
    rect.setPosition(pos.x, pos.y);
    rect.setFillColor(color);
    this->_window.draw(rect);
}
