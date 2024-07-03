/* primefile.h */

#ifndef PRIMEFILE_H
#define PRIMEFILE_H

//typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

/**
 * @file primefile.h This file is base .prime special file type.
 * @author Ahmet Berat
 * @brief 
 * @version 0.2
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

//
// UPDATE: GMPLIB IMPLEMANTATION FOR THE HIGH QUALITY
//         CALCULATION AND MORE SPESIFIC THINGS
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// GMP-LIB Header File
#include <gmpxx.h>
#include <gmp.h>

class PrimeFile {
private:
    std::string filename;
    std::vector<mpz_class> numbers;
    uint32_t count;

public:
    // Varsayılan oluşturucu.
    PrimeFile();

    // Diğer kurucu fonksiyon
    PrimeFile(const std::string& fname, std::vector<mpz_class> nums = {0});
    

    bool writeNumbers();
    bool readNumbers();
    void printNumbers() const;
    bool addNumber(const mpz_class& num);
    

    const std::vector<mpz_class>& getNumbers() const;
    mpz_class getCount() const;

};

bool merge2File(PrimeFile f1, PrimeFile f2, const std::string& outputFilename);

#endif // PRIMEFILE_H