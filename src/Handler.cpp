/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include "Handler.hpp"

Handler::Handler():
    _shell(this)
{
}

void Handler::readInput()
{
    this->_shell.mainLoop();
}
