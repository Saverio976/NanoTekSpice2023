/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** PinLink
*/

#pragma once
#include "BaseError.hpp"

namespace nts
{
    class Pin;

    class PinLink {
        public:
            class InvalidLink: public BaseError
            {
                using BaseError::BaseError;
            };

            PinLink(Pin *in, Pin *out);
            ~PinLink();

            Pin *getOutput();
            Pin *getInput();
        protected:
        private:
            Pin *_input;
            Pin *_output;
    };
}
