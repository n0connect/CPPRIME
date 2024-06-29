/* primefile.h */

#ifndef PRIMEFILE_H
#define PRIMEFILE_H

//typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class PrimeFile {
private:
    std::string filename;
    std::vector<uint32_t> numbers;
    uint32_t count;

public:
    // Varsayılan oluşturucu.
    PrimeFile();

    // Diğer kurucu fonksiyon
    PrimeFile(const std::string& fname, std::vector<uint32_t> nums = {0});
    

    bool writeNumbers();
    bool readNumbers();
    void printNumbers() const;
    bool addNumber(uint32_t num);
    

    const std::vector<uint32_t>& getNumbers() const;
    uint32_t getCount() const;

};

bool merge2File(PrimeFile f1, PrimeFile f2, const std::string& outputFilename);

#endif // PRIMEFILE_H