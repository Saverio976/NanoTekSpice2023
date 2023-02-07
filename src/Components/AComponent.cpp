/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"

std::ostream & operator <<(std::ostream &os, nts::Tristate val)
{
    if (val == nts::True) {
        os << "1";
    } else if (val == nts::False) {
        os << "0";
    } else {
        os << "U";
    }
    return os;
}
