set -e

echo "base components: Testing..."

g++ $(find src/ -name "*.o" -type f -not -name "*main.o") \
    tests/functional/basic_components.cpp   \
    -Iinclude -Isrc/Pin -Isrc/Components -Isrc/Components/Basic -Isrc/Components/InputOutput -Isrc/Components/MultiGate -Isrc \
    -std=c++23 -o base_comp.out

./base_comp.out > tests/functional/tmp.txt
diff tests/functional/table_result.txt tests/functional/tmp.txt --color
echo "base components: OK"
rm -f base_comp.out
rm -f tests/functional/tmp.txt
