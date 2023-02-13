/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** FileParser
*/

#pragma once

#include <cstddef>
#include <exception>
#include <string>

namespace nts
{
    class Handler;

    class FileParser {
        public:
            class FileParsingError : public std::exception {
                public:
                    FileParsingError(const std::string &error);
                    const char *what() const noexcept override;
                private:
                    const std::string _error;
            };

            FileParser(Handler *handler);
            FileParser(const std::string &fileName, Handler *handler);

            void loadFile(const std::string &fileName);

        private:
            enum ParsingType {
                UNKNOWN,
                CHIPSETS,
                LINKS,
            };

            Handler *_handler;

            std::string parseLinkName(const std::string &all) const;
            std::size_t parseLinkPin(const std::string &all) const;
    };
}
