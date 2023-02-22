/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** FileParser
*/

#pragma once

#include <cstddef>
#include <memory>
#include "BaseError.hpp"
#include "Circuit.hpp"

namespace nts
{
    class FileParser {
        public:
            class FileParsingError : public BaseError
            {
                using BaseError::BaseError;
            };

            FileParser(const std::string &fileName, Circuit *circuit);

            void loadFile(const std::string &fileName);

        private:
            enum ParsingType {
                UNKNOWN,
                CHIPSETS,
                LINKS,
            };

            Circuit *_circuit;

            size_t _lineCount = 0;
            const std::string &_fileName;
            ParsingType type = UNKNOWN;
            void handleLine(std::string &line);
            std::string parseLinkName(const std::string &all) const;
            std::size_t parseLinkPin(const std::string &all) const;
    };
}
