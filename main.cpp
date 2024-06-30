/* main.cpp */

#include <iostream>
#include <cstdint>
#include <chrono>
#include <cmath>

// MANUEL LIBS
#include "./src/primefile.h"
#include "./src/primealgorithm.h"

int main() {
    // Süre hesaplaması için <chrono> kütüphanesi eklendi.
    auto start = std::chrono::high_resolution_clock::now();

    PrimeFile listCheck("merged.prime");

    std::cout << "CHECK List first and last item is: ";
    std::cout << listCheck.getNumbers().front() << "  " << listCheck.getNumbers().back() << std::endl;

    std::vector<uint32_t> retVec = parallelPrimeCalculation(
        79999987, 1410065307, listCheck.getNumbers(), 12
    );

    PrimeFile newFile("paralize-0.prime", retVec);

    std::cout << "NEW List first and last item is: ";
    std::cout << newFile.getNumbers().front() << "  " << newFile.getNumbers().back() << std::endl;   

    // Süre hesaplaması için <chrono> kütüphanesi eklendi.
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Süre: " << duration.count() << " milisaniye" << std::endl;

    return 0;
}
