/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include "Handler.hpp"
#include "FileParser.hpp"

FileParser::FileParsingError::FileParsingError(const std::string &error):
    _error(error)
{
}

const char *FileParser::FileParsingError::what() const noexcept
{
    return this->_error.data();
}

FileParser::FileParser(Handler *handler):
    _handler(handler)
{
}

FileParser::FileParser(const std::string &fileName, Handler *handler)
    : _handler(handler)
{
    this->loadFile(fileName);
}

std::string FileParser::parseLinkName(const std::string &all) const
{
    std::string name;

    name = all.substr(0, all.find(':'));
    return name;
}

std::size_t FileParser::parseLinkPin(const std::string &all) const
{
    std::stringstream s;
    std::size_t pin;

    s.str(all.substr(all.find(':') + 1));
    s.exceptions(std::ios::failbit);
    s >> pin;
    return pin;
}

void FileParser::loadFile(const std::string &fileName)
{
    std::string line;
    std::ifstream f;
    ParsingType type = UNKNOWN;

    f.open(fileName);
    if (f.bad() || !f.good() || !f.is_open()) {
        throw FileParsingError("Unable to open file " + fileName);
    }
    while (std::getline(f, line)) {
        std::string rightPart;
        std::string leftPart;
        std::string remainder;
        std::stringstream linestream(line);
        if (line.starts_with("#") || line == "") {
            continue;
        }
        if (line.starts_with(".chipsets:")) {
            type = CHIPSETS;
            continue;
        } else if (line.starts_with(".links:")) {
            type = LINKS;
            continue;
        }
        linestream >> leftPart >> rightPart >> remainder;
        if (remainder != "") {
            linestream.rdbuf();
            linestream << "Bad Line in " << type << ": " << remainder;
            throw FileParsingError(linestream.str());
        }
        if (type == CHIPSETS) {
            this->_handler->addChipset(leftPart, rightPart);
        } else if (type == LINKS) {
            this->_handler->addLink(
                this->parseLinkName(leftPart), this->parseLinkPin(leftPart), 
                this->parseLinkName(rightPart), this->parseLinkPin(rightPart)
            );
        }
    }
    if (!f.eof()) {
        throw FileParsingError("Unable to read file " + fileName);
    }
}
