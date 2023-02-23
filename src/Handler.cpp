/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** Handler
*/

#include <cstddef>
#include <map>
#include <string>
#include "Circuit.hpp"
#include "ComponentFactory.hpp"
#include "FileParser.hpp"
#include "Handler.hpp"
#include "IComponent.hpp"

namespace nts
{
    Handler::Handler():
        _shell(new Shell(this))
    {
    }

    Handler::~Handler()
    {
    }

    void Handler::readInput()
    {
        this->_shell->mainLoop();
    }

    void Handler::loadFile(const std::string &fileName)
    {
        FileParser file(fileName, &this->_circuit);
    }

    std::size_t Handler::getTick() const
    {
        return this->_tick;
    }

    void Handler::incrementTick()
    {
        this->_tick += 1;
    }

    void Handler::syncChipsetTick()
    {
        this->_circuit.syncChipsetTick(this->getTick());
    }

    void Handler::checkGoodParsing() const
    {
        this->_circuit.checkGoodParsing();
    }

    Circuit &Handler::getCircuit()
    {
        return this->_circuit;
    }

    void Handler::changeDefaultShell(Shell *shell)
    {
        this->_shell = shell;
    }
}
