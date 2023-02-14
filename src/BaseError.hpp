/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** BaseError
*/

#pragma once
#include <string>

namespace nts
{
    class BaseError: public std::exception {
        public:
            explicit BaseError(const std::string &error);
            const char *what() const noexcept override;

        protected:
            std::string _error;
    };
}
