#include "SoloGate.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Clock.hpp"
#include "Constants.hpp"
#include <iostream>

nts::Tristate conv(int i)
{
    switch (i) {
        case 0:
            return nts::False;
        case 1:
            return nts::True;
        default:
            return nts::Undefined;
    }
}

int table()
{
    nts::component::IO::Input i1;
    nts::component::IO::Input i2;
    nts::component::IO::Clock c;
    nts::component::IO::TrueInput t;
    nts::component::IO::FalseInput f;
    nts::component::IO::Output o1;
    nts::component::IO::Output o2;
    nts::component::IO::Output o3;
    nts::component::IO::Output o4;
    nts::component::IO::Output o5;
    nts::component::IO::Output o6;
    nts::component::IO::Output o7;
    nts::component::IO::Output o8;
    nts::component::AndGate g1;
    nts::component::OrGate g2;
    nts::component::XorGate g3;
    nts::component::NandGate g4;
    nts::component::NorGate g5;
    size_t tick = 1;

    c.setValue(nts::False);
    auto call = [&](nts::Tristate l, nts::Tristate r)
    {
        i1.setValue(l);
        i2.setValue(r);
        tick += 1;
        o1.simulate(tick);
        o2.simulate(tick);
        o3.simulate(tick);
        o4.simulate(tick);
        o5.simulate(tick);
        o6.simulate(tick);
        o7.simulate(tick);
        o8.simulate(tick);
        std::cout << "|" << l << "|" << r << "| " << o1.getValue() << " |" << o2.getValue() << " | " << o3.getValue() << " | ";
        std::cout << o4.getValue() << "  | " << o5.getValue() << " |  " << o6.getValue() << "  | ";
        std::cout << o7.getValue() << "  |  " << o8.getValue() << "  |" <<  std::endl;;
    };

    auto list = [&]()
    {
        std::cout << "|A|B|AND|OR|XOR|NAND|NOR|CLOCK|TRUE|FALSE|" << std::endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                call(conv(i), conv(j));
            }
        }
    };

    g1.setLink(1, i1, 1);
    g1.setLink(2, i2, 1);
    g1.setLink(3, o1, 1);
    g2.setLink(1, i1, 1);
    g2.setLink(2, i2, 1);
    g2.setLink(3, o2, 1);
    g3.setLink(1, i1, 1);
    g3.setLink(2, i2, 1);
    g3.setLink(3, o3, 1);
    g4.setLink(1, i1, 1);
    g4.setLink(2, i2, 1);
    g4.setLink(3, o4, 1);
    g5.setLink(1, i1, 1);
    g5.setLink(2, i2, 1);
    g5.setLink(3, o5, 1);
    c.setLink(1, o6, 1);
    t.setLink(1, o7, 1);
    f.setLink(1, o8, 1);

    list();


    return 1;
}

int main()
{
    table();
}
