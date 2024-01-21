#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <iostream>
#include <Fundamental/Interface/IReferenced.h>

int main(int argc, char** argv) {
    auto g = boost::uuids::random_generator()();
    std::cout << "{ ";
    for (int i = 0; i < 16; ++i) {
        if (i != 0) std::cout << ", ";

        std::cout << std::hex << std::showbase << (unsigned)g.data[i];
    }
    std::cout << " }" << std::endl;
}
