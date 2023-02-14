/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** FileParser
*/

#pragma once

#include <cstddef>
#include "BaseError.hpp"

namespace nts
{
    class Handler;

    class FileParser {
        public:
            class FileParsingError : public BaseError
            {
                using BaseError::BaseError;
            };

            FileParser(const std::string &fileName, Handler *handler);

            void loadFile(const std::string &fileName);

        private:
            enum ParsingType {
                UNKNOWN,
                CHIPSETS,
                LINKS,
            };

            Handler *_handler;

            size_t line_count = 0;
            const std::string &_fileName;
            ParsingType type = UNKNOWN;
            void handleLine(std::string &line);
            std::string parseLinkName(const std::string &all) const;
            std::size_t parseLinkPin(const std::string &all) const;
    };
}
