/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <fstream>
#include <ios>
#include <sstream>
#include <algorithm>
#include <string>
#include "Circuit.hpp"
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
    FileParser::FileParser(const std::string &fileName, Circuit *circuit):
        _circuit(circuit),
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
        try {
            s >> pin;
        } catch (const std::ios_base::failure &e) {
            throw FileParsingError("Invalid pin number for link [" + all + "].");
        }
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
        if (type == UNKNOWN) {
            throw FileParsingError("Instruction outside of label");
        }
        linestream >> leftPart >> rightPart;
        if (linestream.rdbuf()->in_avail() != 0 || rightPart == "") {
            throw FileParsingError("Too many arguments (need exactly 2).");
        }
        if (type == CHIPSETS) {
            if (std::count(rightPart.begin(), rightPart.end(), ':') != 0) {
                throw FileParsingError("Invalid chipset name, must not contain ':'");
            }
            this->_circuit->addChipset(leftPart, rightPart);
        } else if (type == LINKS) {
            this->_circuit->addLink(
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
            _lineCount += 1;
            trim_line(line);
            try {
                handleLine(line);
            } catch (const BaseError &e) {
                throw FileParsingError(_fileName + ":" + std::to_string(_lineCount) + ": " + e.what() + "\n" + std::to_string(_lineCount) + ">" + line);
            }
        }
        if (!f.eof()) {
            throw FileParsingError("Unable to read file " + fileName);
        }
        this->_circuit->checkGoodParsing();
    }
}
