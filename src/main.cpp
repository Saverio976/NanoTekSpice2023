/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** main
*/

#include <cstdlib>
#include <iostream>
#include "Handler.hpp"

int main(int argc, const char *const argv[])
{
    Handler handler;

    if (argc != 2) {
        exit(84);
    }
    try {
        handler.loadFile(argv[1]);
        handler.readInput();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(84);
    }
    return 0;
}
