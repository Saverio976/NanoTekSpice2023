/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** main
*/

#include "Handler.hpp"

int main(int argc, const char *const argv[])
{
    Handler handler;

    if (argc > 1) {
        handler.loadFile(argv[1]);
    }
    return 0;
}
