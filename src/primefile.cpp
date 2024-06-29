/* primefile.cpp */

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "primefile.h"

/**
 * @brief Construct a new Prime File:: Prime File object
 * 
 */
PrimeFile::PrimeFile() : filename(""), count(0) {}

/**
 * @brief Construct a new Prime File:: Prime File object
 * 
 * @param fname 
 * @param nums 
 */
PrimeFile::PrimeFile(const std::string& fname, std::vector<uint32_t> nums) : filename(fname), numbers(nums), count(nums.size()) {
    // Dosyayı okumak için
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        
        // Dosya yoksa, boş bir dosya oluştur
        std::ofstream newFile(filename, std::ios::binary);
        
        if(!writeNumbers()){
            std::cerr << "\033[0;31mWrite number's error" << std::endl;
        }

        newFile.close();
    
    } else {
        // Dosya varsa sayıları oku
        
        if(!readNumbers()){
            std::cerr << "\033[0;31mRead file error" << std::endl;
        }
    }
}

/**
 * @brief writeNumbers dosyaya ikinci parametre olarak aldığı vektörü yazdırır.
 * 
 * @return true 
 * @return false 
 */
bool PrimeFile::writeNumbers() {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "\033[0;31mFile open error!" << std::endl;
        return false;
    }

    for (uint32_t num : numbers) {
        file.write(reinterpret_cast<const char*>(&num), sizeof(uint32_t));
    }

    file.close();
    return true;
}

/**
 * @brief readNumbers dosyada yazılı olan değerleri okur.
 * 
 * @return true 
 * @return false 
 */
bool PrimeFile::readNumbers() {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "\033[0;31mFile open error!" << std::endl;
        return false;
    }

    numbers.clear(); // Mevcut sayıları temizle

    uint32_t num;
    while (file.read(reinterpret_cast<char*>(&num), sizeof(uint32_t))) {
        numbers.push_back(num);
    }

    count = numbers.size(); // Sayı adedini güncelle

    file.close();
    return true;
}

/**
 * @brief printNumbers dosyadan alınan sayıları konsola yazdırır.
 * 
 */
void PrimeFile::printNumbers() const {
    std::cout << "Number in the file:" << std::endl;

    std::cout << "\033[1;32m[ ";

    for (uint32_t num : numbers) {
        std::cout << num << ", ";
    }

    std::cout << "\b\b" << "\033[1;32m ]" << std::endl;

    std::cout << std::endl;
}

/**
 * @brief addNumber dosyaya bir adet sayı ekler.
 * 
 * @param num 
 * @return true 
 * @return false 
 */
bool PrimeFile::addNumber(uint32_t num) {
    numbers.push_back(num);
    count++;
    return true; // Basitlik için başarılı kabul ediyoruz
}

/**
 * @brief getNumbers dosyanın bağlı olduğu vektörü döndürür.
 * 
 * @return const std::vector<uint32_t>& 
 */
const std::vector<uint32_t>& PrimeFile::getNumbers() const {
    return numbers;
}

/**
 * @brief Dosyanın içerdiği sayı adedini gösterir.
 * 
 * @return uint32_t 
 */
uint32_t PrimeFile::getCount() const {
    return count;
}

/**
 * @brief iki ader .prime dosyasını birleştirerek ted dosya haline getirir.
 * 
 * @param f1 
 * @param f2 
 * @param outputFilename 
 * @return true 
 * @return false 
 */
bool merge2File(PrimeFile f1, PrimeFile f2, const std::string& outputFilename) {
    const std::vector<uint32_t>& numbers1 = f1.getNumbers();
    const std::vector<uint32_t>& numbers2 = f2.getNumbers();

    std::vector<uint32_t> mergedNumbers;
    mergedNumbers.reserve(numbers1.size() + numbers2.size());

    // İki listeyi birleştir
    std::merge(numbers1.begin(), numbers1.end(), numbers2.begin(), numbers2.end(), std::back_inserter(mergedNumbers));

    // Tekrarlayan değerleri kaldırmak için
    auto last = std::unique(mergedNumbers.begin(), mergedNumbers.end());
    mergedNumbers.erase(last, mergedNumbers.end());

    // Yeni PrimeFile nesnesi oluştur ve sayıları yaz
    PrimeFile outputFile(outputFilename, mergedNumbers);
    return outputFile.writeNumbers();
}