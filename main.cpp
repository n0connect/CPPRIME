/* main.cpp */

#include <iostream>
#include <cstdint>
#include <chrono>
#include <cmath>

// MANUEL LIBS
#include "./src/primefile.h"
#include "./src/primealgorithm.h"

// GMP IMPLEMENTATION
#include <gmpxx.h>
#include <gmp.h>

void mergeFile(const char* fn1, const char* fn2){
    PrimeFile f1(fn1);
    PrimeFile f2(fn2);
    bool rt = merge2File(f1, f2, "merged.prime");

    if(rt){
        std::clog << "Merged";
    }else{
        std::cerr << "Not Merged";
    }
}

void seekFile(const char* fn){
    PrimeFile file(fn);
    file.printNumbers();

    std::vector<mpz_class> ret = file.getNumbers();

    std::cout << "Total Prime number at file: " << file.getCount() << std::endl;
    std::cout << "First and Last element of file: " << ret.front() << " - " << ret.back() << std::endl;

}

void betterChoice(mpz_class startNum, mpz_class endNum, mpz_class numThread){
    //
    // CALCULATION FOR BETTER WORK SPACE
    //
    mpz_class diffrence = endNum - startNum;
    mpz_class dvide = diffrence/numThread;
    std::cout << dvide << "\n";
    for(mpz_class i = 1; i < 150/*sqrt(dvide) + 1*/; ++i){
        mpz_class first = i;
        mpz_class second = dvide/i;
        
        std::cout << "("<< first << ", " << second << ")" << " = " <<
            first*second << "   |   " << first*second - dvide << "\n";
    }
}

int main() {
    const uint32_t numThread = 12;
    const uint32_t chunkCount = 80, chunkRange= 1385484;
    mpz_class startNum;
    mpz_class endNum;
    startNum = "79999987";
    endNum   = "1410065307";

    //betterChoice(startNum, endNum, 12);
    //exit(1);
    
    // For the time calculation added <chrono> lib.
    auto start = std::chrono::high_resolution_clock::now();

    // Open the base-control file.
    PrimeFile listCheck("p0.prime");

    // Create Parallel Task for the calculate between start to stop values.
    std::vector<mpz_class> retVec = parallelPrimeCalculation(
        startNum, endNum, listCheck.getNumbers(), numThread, chunkCount, chunkRange
    );

    // End time for the calculation time.
    auto end = std::chrono::high_resolution_clock::now();

    // SAVE THE CALCULATION
    PrimeFile calculatedList("p1.prime", retVec);
    calculatedList.printNumbers();
    

    // Calculation result.
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " milisecond" << std::endl;

    return 0;
}
