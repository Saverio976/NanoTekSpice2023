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
    s >> pin;
    return pin;
}

void FileParser::loadFile(const std::string &fileName)
{
    std::string line;
    std::stringstream linestream;
    std::ifstream f;
    ParsingType type = UNKNOWN;
    std::string part1Parsed;
    std::string part2Parsed;

    f.open(fileName);
    if (f.bad() || !f.good() || !f.is_open()) {
        throw FileParsingError("Unable to open file " + fileName);
    }
    while (std::getline(f, line)) {
        if (line.starts_with("#")) {
            continue;
        }
        if (line.starts_with(".chipsets:")) {
            type = CHIPSETS;
            continue;
        } else if (line.starts_with(".links:")) {
            type = LINKS;
            continue;
        }
        linestream.str(line);
        linestream >> part1Parsed >> part2Parsed;
        if (type == CHIPSETS) {
            this->_handler->addChipset(part1Parsed, part2Parsed);
        } else if (type == LINKS) {
            this->_handler->addLink(
                this->parseLinkName(part1Parsed), this->parseLinkPin(part1Parsed), 
                this->parseLinkName(part2Parsed), this->parseLinkPin(part2Parsed)
            );
        }
    }
    if (f.bad() || !f.good() || !f.is_open()) {
        throw FileParsingError("Unable to read file " + fileName);
    }
}
