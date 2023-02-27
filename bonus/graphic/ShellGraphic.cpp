//
// EPITECH PROJECT, 2023
// nano
// File description:
// shell in graphics mode
//

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include "ComponentFactory.hpp"
#include "IComponent.hpp"
#include "ShellGraphic.hpp"
#include "Shell.hpp"
#include "Handler.hpp"
#include "Pin.hpp"

ShellGraphic::ShellGraphic(nts::Handler *handler):
    Shell(handler),
    _window(sf::VideoMode(800, 600), "NanoTekSpice", sf::Style::Close)
{
    this->_window.setVerticalSyncEnabled(true);
    if (!this->_font.loadFromFile("bonus/graphic/fira_code_nerd_font.ttf")) {
        this->_font.loadFromFile("fira_code_nerd_font.ttf");
    }
    this->initInputBox();
    this->initSimulateBox();
    this->initQuitBox();
}

void ShellGraphic::mainLoop()
{
    sf::Clock clock;
    sf::Clock cl_simulate;

    this->initInputs();
    this->initOutputs();
    this->initOtherGates();
    while (this->_isEnd == false && this->_window.isOpen()) {
        this->draw();
        sf::Event event;
        while (this->_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->_window.close();
                continue;
            }
            if ((
                    (
                        event.type == sf::Event::KeyPressed &&
                        (
                            event.key.code == sf::Keyboard::Backspace ||
                            event.key.code == sf::Keyboard::Delete)
                        ) ||
                    (
                        event.type == sf::Event::TextEntered &&
                        (
                            event.text.unicode == 8 ||
                            event.text.unicode == 127
                        )
                    )) && this->_inputBoxString.length() >= 1) {
                if (clock.getElapsedTime().asSeconds() < 0.1) {
                    continue;
                }
                clock.restart();
                this->_inputBoxString = this->_inputBoxString.substr(0, this->_inputBoxString.length() - 1);
                this->_inputBoxText.setString(this->_inputBoxString);
                continue;
            }
            if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Enter &&
                    this->_inputBoxString.length() >= 1) {
                try {
                    this->interpretLine(this->_inputBoxString);
                } catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
                this->_inputBoxString.clear();
                this->_inputBoxText.setString(this->_inputBoxString);
                continue;
            }
            if (event.type == sf::Event::TextEntered) {
                char c = event.text.unicode;
                if (!std::isprint(c)) {
                    continue;
                }
                this->_inputBoxString += c;
                this->_inputBoxText.setString(this->_inputBoxString);
                continue;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (cl_simulate.getElapsedTime().asSeconds() < 0.1) {
                    continue;
                }
                if (this->_simulateBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    this->interpretLine("simulate");
                    cl_simulate.restart();
                    continue;
                }
                if (this->_quitBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    this->interpretLine("exit");
                    cl_simulate.restart();
                    continue;
                }
            }
        }
    }
}

void ShellGraphic::draw()
{
    this->_window.clear(sf::Color::Black);
    for (auto &gate : this->_gates) {
        this->drawGate(gate.getName(), gate.getPosition(), gate.getSize(), gate.getColor());
        this->drawGatesLinks(gate);
    }
    this->_window.draw(this->_inputBox);
    this->_window.draw(this->_inputBoxText);
    this->_window.draw(this->_simulateBox);
    this->_window.draw(this->_simulateText);
    this->_window.draw(this->_quitBox);
    this->_window.draw(this->_quitText);
    this->_window.display();
}

void ShellGraphic::initInputs()
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
            auto gate = this->_handler->getCircuit().getChipset(input);
            this->_gates.push_back(PositionGate(pos, size, sf::Color::Blue, gate, input));
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::initOutputs()
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
            auto gate = this->_handler->getCircuit().getChipset(output);
            this->_gates.push_back(PositionGate(pos, size, sf::Color::Magenta, gate, output));
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::initOtherGates()
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
        if (std::find(this->_outputsType.begin(), this->_outputsType.end(), type) != this->_outputsType.end()) {
            continue;
        }
        try {
            components = this->_handler->getCircuit().getChipsetNames(type);
        } catch (...) {
            continue;
        }
        for (auto &component : components) {
            auto gate = this->_handler->getCircuit().getChipset(component);
            this->_gates.push_back(PositionGate(pos, size, sf::Color::Red, gate, component));
            pos.y += size.y + this->_padding_middle;
        }
    }
}

void ShellGraphic::initInputBox()
{
    this->_inputBox.setPosition(
        sf::Vector2f(this->_padding_extern, this->_window.getSize().y * (0.75))
    );
    this->_inputBox.setSize(sf::Vector2f(
        this->_window.getSize().x - (2 * this->_padding_extern),
        (this->_window.getSize().y - this->_padding_extern) - (this->_window.getSize().y * (0.75))
    ));
    this->_inputBox.setFillColor(sf::Color::White);
    this->_inputBoxText.setPosition(
        this->_inputBox.getPosition().x + this->_padding_middle,
        this->_inputBox.getPosition().y + this->_padding_middle
    );
    this->_inputBoxText.setFont(this->_font);
    this->_inputBoxText.setString(this->_inputBoxString);
    this->_inputBoxText.setFillColor(sf::Color::Black);
}

void ShellGraphic::drawGate(const std::string &name, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color)
{
    auto component = this->_handler->getCircuit().getChipset(name);
    sf::RectangleShape rect(size);
    sf::Text text;

    if (component == nullptr) {
        return;
    }
    rect.setPosition(pos.x, pos.y);
    rect.setFillColor(color);
    this->_window.draw(rect);
    text.setString(name);
    text.setPosition(pos);
    text.setFont(this->_font);
    text.setCharacterSize(15);
    this->_window.draw(text);
}

static sf::Color getColorFromValue(nts::Tristate value)
{
    if (value == nts::Tristate::Undefined) {
        return sf::Color::Red;
    }
    if (value == nts::Tristate::False) {
        return sf::Color::White;
    }
    if (value == nts::Tristate::True) {
        return sf::Color::Blue;
    }
    return sf::Color::White;
}

void ShellGraphic::drawGatesLinks(PositionGate &gate)
{
    for (auto &pin : gate.getComponent()->getPins()) {
        const auto source = pin.second->getSource();
        if (source == nullptr) {
            continue;
        }
        for (auto &target : this->_gates) {
            if (target.getComponent() != &source->getParent()) {
                continue;
            }
            sf::Vertex line[] = {
                sf::Vertex(
                    sf::Vector2f(target.getPosition().x, target.getPosition().y),
                    getColorFromValue(source->getValue())
                ),
                sf::Vertex(
                    sf::Vector2f(gate.getPosition().x, gate.getPosition().y),
                    getColorFromValue(pin.second->getValue())
                )
            };
            this->_window.draw(line, 2, sf::Lines);
            break;
        }
    }
}

void ShellGraphic::initSimulateBox()
{
    this->_simulateBox.setFillColor(sf::Color::White);
    this->_simulateText.setFont(this->_font);
    this->_simulateText.setCharacterSize(15);
    this->_simulateText.setFillColor(sf::Color::Black);
    this->_simulateText.setString("Simulate");
    this->_simulateBox.setSize(sf::Vector2f(
        this->_simulateText.getGlobalBounds().width,
        this->_simulateText.getGlobalBounds().height
    ));
    this->_simulateBox.setPosition(
        this->_inputBox.getPosition().x,
        this->_inputBox.getPosition().y - (this->_simulateBox.getSize().y + this->_padding_middle)
    );
    this->_simulateText.setPosition(
        this->_simulateBox.getPosition().x,
        this->_simulateBox.getPosition().y - this->_padding_middle
    );
}

void ShellGraphic::initQuitBox()
{
    this->_quitBox.setFillColor(sf::Color::White);
    this->_quitText.setFont(this->_font);
    this->_quitText.setCharacterSize(15);
    this->_quitText.setFillColor(sf::Color::Black);
    this->_quitText.setString("Quit");
    this->_quitBox.setSize(sf::Vector2f(
        this->_quitText.getGlobalBounds().width,
        this->_quitText.getGlobalBounds().height
    ));
    this->_quitBox.setPosition(
        this->_simulateBox.getPosition().x,
        this->_simulateBox.getPosition().y - (this->_quitBox.getSize().y + this->_padding_middle)
    );
    this->_quitText.setPosition(
        this->_quitBox.getPosition().x,
        this->_quitBox.getPosition().y - this->_padding_middle
    );
}
