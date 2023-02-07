/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include "Handler.hpp"
#include "FileParser.hpp"

void Handler::loadFile(const std::string &fileName)
{
    FileParser file(fileName, this);
}
