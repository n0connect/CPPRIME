/* main.cpp */

#include <iostream>
#include <cstdint>
#include <cmath>

// MANUEL LIBS
#include "./src/primefile.h"
#include "./src/primealgorithm.h"

void SUCK(){
    std::cout << "-> in main function" << std::endl;

    PrimeFile listCheck("merged.prime");

    std::vector<uint32_t> retVec = parallelPrimeCalculation(
        79999987, 100000000, listCheck.getNumbers(), 8
    );

    PrimeFile newFile("paralize.prime", retVec);
}

int main() {

    PrimeFile listCheck("merged.prime");

    std::cout << "CHECK List first and last item is : ";
    std::cout << listCheck.getNumbers().front() << "  " << listCheck.getNumbers().back() << std::endl;

    std::vector<uint32_t> retVec = parallelPrimeCalculation(
        79999987, 1410065307, listCheck.getNumbers(), 8
    );

    PrimeFile newFile("paralize-0.prime", retVec);

    std::cout << " NEW List first and last item is : ";
    std::cout << newFile.getNumbers().front() << "  " << newFile.getNumbers().back() << std::endl;   

    return 0;
}
