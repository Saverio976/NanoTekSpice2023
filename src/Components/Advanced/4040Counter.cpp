/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** 4040Counter
*/

#include <iostream>
#include "4040Counter.hpp"

const std::map<size_t, size_t> nts::component::Component4040::_indexMap = {
    {9, 1},
    {7, 2},
    {6, 3},
    {5, 4},
    {3, 5},
    {2, 6},
    {4, 7},
    {13, 8},
    {12, 9},
    {14, 10},
    {15, 11},
    {1, 12},
};

namespace nts::component
{
    Component4040::Component4040()
    {
        _pins.push_back(Pin(*this, Pin::INPUT, 10));
        _pins.push_back(Pin(*this, Pin::INPUT, 11));

        for (auto &pair: _indexMap) {
            _pins.push_back(Pin(*this, Pin::OUTPUT, pair.first));
            _pinMap[pair.first] = &_pins.back();
        }
    }

    nts::Tristate Component4040::compute(std::size_t pin)
    {
        if (pin == 11) {
            (*this)[11].simulate(_lastTick);
            if ((*this)[11].getValue() == nts::True) {
                reset();
            }
            return ((*this)[11].getValue());
        } else if (pin == 10) {
            (*this)[10].simulate(_lastTick);
            if ((*this)[10].getValue() == nts::True) {
                increment();
            }
            return (*this)[10].getValue();
        } else if (_pinMap.contains(pin)) {
            if ((*this)[10].getValue() == nts::Undefined || (*this)[11].getValue() == nts::Undefined) {
                return nts::Undefined;
            }
            if (_counter & (1 << (_indexMap.at(pin) - 1))) {
                return nts::True;
            } else {
                return nts::False;
            }
        } else {
            throw Pin::BadPin("4040: No pin n°" + std::to_string(pin));
        }
    }

    void Component4040::simulate(std::size_t tick)
    {
        nts::Tristate oldValue;

        auto call = [&](size_t pin) {
            oldValue = (*this)[pin].getValue();
            (*this)[pin].setValue(this->compute(pin));
            if (oldValue != (*this)[pin].getValue() && (*this)[pin].getPinType() == Pin::INPUT) {
                _hasChanged = true;
            }
        };

        if (_lastTick == tick && !_hasChanged) {
            return;
        }
        _lastTick = tick;
        _hasChanged = false;

        call(10);
        call(11);

        for (size_t i = 1; i < 16; i++) {
            if (i == 8 || i == 10 || i == 11) {
                continue;
            }
            (*this)[i].setValue(this->compute(i));
        }
    }

    nts::IComponent* Component4040::clone() const
    {
        return new Component4040();
    }

    void Component4040::reset()
    {
        _counter = 0;
    }

    void Component4040::increment()
    {
        if (_lastIncrement == _lastTick) {
            return;
        }
        _lastIncrement = _lastTick;
        _counter += 1;
    }

    Pin& Component4040::operator [](size_t pin)
    {
        if (_pinMap.contains(pin)) {
            return *_pinMap[pin];
        } else if (pin == 10) {
            return _pins[0];
        } else if (pin == 11) {
            return _pins[1];
        } else {
            throw Pin::BadPin("4040: No pin n°" + std::to_string(pin));
        }
    }
}
