set -e

echo "base components: Testing..."

g++ src/Components/AComponent.o                        \
    src/Components/Basic/Inverter.o                    \
    src/Components/Basic/SoloGate.o                    \
    src/Components/ComponentFactory.o                    \
    src/Components/InputOutput/Clock.o                \
    src/Components/InputOutput/Constants.o            \
    src/Components/InputOutput/Input.o                \
    src/Components/InputOutput/Output.o                \
    src/Components/MultiGate/Component4069.o            \
    src/FileParser.o                                    \
    src/Handler.o                                        \
    src/Pin/Pin.o                                        \
    src/Pin/PinLink.o                                        \
    src/Shell.o \
    src/BaseError.o \
    tests/functional/basic_components.cpp   \
    -Iinclude -Isrc/Pin -Isrc/Components -Isrc/Components/Basic -Isrc/Components/InputOutput -Isrc/Components/MultiGate -Isrc \
    -std=c++23 -o base_comp.out

./base_comp.out > tests/functional/tmp.txt
diff tests/functional/table_result.txt tests/functional/tmp.txt --color
echo "base components: OK"
rm -f base_comp.out
rm -f tests/functional/tmp.txt
