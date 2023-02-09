/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** PinLink
*/

#pragma once

class Pin;

class PinLink {
    public:
        PinLink(Pin *in, Pin *out);
        ~PinLink();

        Pin *getOutput();
        Pin *getInput();
    protected:
    private:
        Pin *_input;
        Pin *_output;
};
