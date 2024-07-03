/* primefile.cpp */

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

// Manuel Header
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
PrimeFile::PrimeFile(const std::string& fname, std::vector<mpz_class> nums) : filename(fname), numbers(nums), count(nums.size()) {
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

    /***************************************** */
    for (const auto& num : numbers) {
        std::string num_str = num.get_str();
        uint32_t size = num_str.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
        file.write(num_str.c_str(), size);
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

    uint32_t size;
    while (file.read(reinterpret_cast<char*>(&size), sizeof(uint32_t))) {
        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        numbers.push_back(mpz_class(std::string(buffer.data(), size)));
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

    for (const auto& num : numbers) {
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
bool PrimeFile::addNumber(const mpz_class& num) {
    numbers.push_back(num);
    count++;
    return true; // Basitlik için başarılı kabul ediyoruz
}

/**
 * @brief getNumbers dosyanın bağlı olduğu vektörü döndürür.
 * 
 * @return const std::vector<mpz_class>& 
 */
const std::vector<mpz_class>& PrimeFile::getNumbers() const {
    return numbers;
}

/**
 * @brief Dosyanın içerdiği sayı adedini gösterir.
 * 
 * @return mpz_class 
 */
mpz_class PrimeFile::getCount() const {
    return count;
}

/**
 * @brief iki ader .prime dosyasını birleştirerek tek dosya haline getirir.
 * 
 * @param f1 
 * @param f2 
 * @param outputFilename 
 * @return true 
 * @return false 
 */
bool merge2File(PrimeFile f1, PrimeFile f2, const std::string& outputFilename) {
    const std::vector<mpz_class>& numbers1 = f1.getNumbers();
    const std::vector<mpz_class>& numbers2 = f2.getNumbers();

    std::vector<mpz_class> mergedNumbers;
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