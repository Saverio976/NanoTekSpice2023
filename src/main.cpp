/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** main
*/

#include <iostream>
#include <string.h>
#include "Handler.hpp"

static void display_help(const char *exec)
{
    std::cout << "Usage: " << exec << " [circuit_file.nts]" << std::endl << std::endl;
    std::cout << "Simulates electronics components" << std::endl;
    std::cout << "Circuit file contains info on both what chipset are used and how they are linked" << std::endl;
    std::cout << "You can find example files in tests/nts_files" << std::endl;
    std::cout << "Here is a list of components (you can read more on how they work in the documentation folder):" << std::endl << std::endl;

    std::cout << "\tSpecial components:" << std::endl;
    std::cout << "\t\tinput: a component with a single pin directly linked to the command line. Its value is initialized to undefined." << std::endl;
    std::cout << "\t\tclock: a component that works like an input, except its value is inverted after each simulation." << std::endl;
    std::cout << "\t\ttrue: a component with a single pin that is always true." << std::endl;
    std::cout << "\t\tfalse: a component with a single pin that is always false." << std::endl;
    std::cout << "\t\toutput: a component with a single pin used as the output of a circuit." << std::endl;

    std::cout << "\tElementary components:" << std::endl;
    std::cout << "\t\tand: single AND gate." << std::endl;
    std::cout << "\t\tor: single OR gate." << std::endl;
    std::cout << "\t\txor: single XOR gate." << std::endl;
    std::cout << "\t\tnot: single INVERTER gate." << std::endl;

    std::cout << "\tGates components:" << std::endl;
    std::cout << "\t\t4001: Four NOR gates." << std::endl;
    std::cout << "\t\t4011: Four NAND gates." << std::endl;
    std::cout << "\t\t4030: Four XOR gates." << std::endl;
    std::cout << "\t\t4069: Six INVERTER gates." << std::endl;
    std::cout << "\t\t4071: Four OR gates." << std::endl;
    std::cout << "\t\t4081: Four AND gates." << std::endl;

    std::cout << "\tAdvanced components:" << std::endl;
    std::cout << "\t\t4008: 4 bits adder." << std::endl;
    std::cout << "\t\t4013: Dual Flip Flop." << std::endl;
    std::cout << "\t\t4017: 10 bits Johnson decade." << std::endl;
    std::cout << "\t\t4040: 12 bits counter." << std::endl;
    std::cout << "\t\t4094: 8 bits shift register." << std::endl;
    std::cout << "\t\t4512: 8 channel data selector." << std::endl;
    std::cout << "\t\t4514: 4 bits decoder." << std::endl;
    std::cout << "\t\t4801: Random access memory." << std::endl;
    std::cout << "\t\t2716: Read only memory (memory initialized from ./rom.bin)" << std::endl;
}

int main(int argc, const char *const argv[])
{
    nts::Handler handler;

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [circuit_file.nts]" << std::endl;
        std::cout << "Try '" << argv[0] << " --help' for more information." << std::endl;
        return 84;
    }
    if (strcmp(argv[1], "--help") == 0) {
        display_help(argv[0]);
        return 0;
    }
    try {
        handler.loadFile(argv[1]);
        handler.readInput();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
