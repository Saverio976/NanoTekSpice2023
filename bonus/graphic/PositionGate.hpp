//
// EPITECH PROJECT, 2023
// nano
// File description:
// position of gate on the map
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "IComponent.hpp"

class PositionGate
{
    public:
        PositionGate(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color, nts::IComponent *component, const std::string &name);

        const sf::Vector2f &getPosition() const;
        const sf::Vector2f &getSize() const;
        void setPosition(sf::Vector2f pos);
        void setSize(sf::Vector2f size);
        nts::IComponent *getComponent();
        const std::string &getName() const;
        const sf::Color &getColor() const;

    protected:
        sf::Vector2f _position;
        sf::Vector2f _size;
        sf::Color _color;
        nts::IComponent *_component;
        std::string _name;
};
