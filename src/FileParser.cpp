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
#include "string.h"
#include "Handler.hpp"
#include "FileParser.hpp"

static void trim_line(std::string &str)
{
    size_t index = 0;

    index = str.find("#");
    if (index != std::string::npos) {
        str = str.substr(0, index);
    }

    index = str.find_first_not_of(" \t");
    str = (index == std::string::npos) ? "" : str.substr(index);
    index = str.find_last_not_of(" \t");
    str = (index == std::string::npos) ? "" : str.substr(0, index + 1);
}

namespace nts
{
    FileParser::FileParser(const std::string &fileName, Handler *handler)
        : _handler(handler),
        _fileName(fileName)
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

    void FileParser::handleLine(std::string &line)
    {
        std::string rightPart;
        std::string leftPart;
        std::string remainder;
        std::stringstream linestream(line);
        if (line == "") {
            return;
        }
        if (line.starts_with(".chipsets:")) {
            type = CHIPSETS;
            return;
        } else if (line.starts_with(".links:")) {
            type = LINKS;
            return;
        }
        linestream >> leftPart >> rightPart;
        if (linestream.rdbuf()->in_avail() != 0 || rightPart == "") {
            throw FileParsingError(_fileName + ":" + std::to_string(line_count) + ": Invalid line, too many arguments (need exactly 2).\n" + line);
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

    void FileParser::loadFile(const std::string &fileName)
    {
        std::string line;
        std::ifstream f;

        f.open(fileName);
        if (f.bad() || !f.good() || !f.is_open()) {
            throw FileParsingError("Unable to open file " + fileName);
        }
        while (std::getline(f, line)) {
            trim_line(line);
            handleLine(line);
        }
        if (!f.eof()) {
            throw FileParsingError("Unable to read file " + fileName);
        }
        this->_handler->checkGoodParsing();
    }
}
