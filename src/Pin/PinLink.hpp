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
        PinLink();
        ~PinLink();

    protected:
    private:
        Pin *_input;
        Pin *_output;
};
