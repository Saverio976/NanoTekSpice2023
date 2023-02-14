/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** BaseError
*/

#include "BaseError.hpp"

namespace nts
{
    BaseError::BaseError(const std::string &error)
    {
        _error = error;
    }

    const char *BaseError::what() const noexcept
    {
        return _error.data();
    }
}
