//
// EPITECH PROJECT, 2023
// nano
// File description:
// position gate
//

#include "PositionGate.hpp"
#include "IComponent.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

PositionGate::PositionGate(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color, nts::IComponent *component, const std::string &name):
    _position(pos), _size(size), _color(color), _component(component), _name(name)
{
}

const sf::Vector2f &PositionGate::getPosition() const
{
    return this->_position;
}

const sf::Vector2f &PositionGate::getSize() const
{
    return this->_size;
}

void PositionGate::setPosition(sf::Vector2f pos)
{
    _position = pos;
}

void PositionGate::setSize(sf::Vector2f size)
{
    _size = size;
}

nts::IComponent *PositionGate::getComponent()
{
    return this->_component;
}

const std::string &PositionGate::getName() const
{
    return this->_name;
}

const sf::Color &PositionGate::getColor() const
{
    return this->_color;
}
