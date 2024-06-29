/* primealgorithm.cpp */

#include "primealgorithm.h"
#include "primefile.h"

/**
 * @brief KOnsol ekranında bulunacak olan işlem çubuğu.
 * 
 * @param progress 
 */
void loadingBar(double progress) {
    int barWidth = 70;
    int pos = barWidth * progress;
    std::cout << "\033[1;32m[ ";

    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "\033[1;32m=";
        else if (i == pos) std::cout << "\033[1;32m>";
        else std::cout << " ";
    }

    std::cout << "\033[1;32m ] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

/**
 * @brief Start ve Stop değerleri arasında bulunan asal sayıları tespit eder.
 * 
 * @param start 
 * @param stop 
 * @param plist 
 * @return std::vector<uint32_t> 
 */
std::vector<uint32_t> calculateBetween(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist) {
    
    bool     primeCheck = true;
    uint32_t marginErr  =   10;
    
    std::vector<uint32_t> primeList = *cropPrimeList(plist, static_cast<uint32_t>(sqrtf(stop) + marginErr));
    std::vector<uint32_t> saveVec;

    uint32_t total   = (stop - start) / 2;
    uint32_t partJob =        total / 100;
    uint32_t dump    =                  1;

    //
    // Girilen sayıların tek olup olmadığını kontrol et
    //
    if(start % 2 == 0){
        std::clog << "Start number is not odd substracting 1" << std::endl;
        start--;
    }

    //
    // Terminal Manipülasyonu
    //
    std::cout << "Calculating numbers between " << start << " and " << stop << "\n";

    for (uint32_t i = start; i < stop; i += 2) {
        // Loading bar'ı güncelle
        if (i % partJob == 1) { 
            loadingBar(static_cast<double>(i - start) / (stop - start));
        }

        for (uint32_t prime : primeList) {
            if (i % prime == 0) { 
                primeCheck = false; 
                break; 
            }
        }

        if (primeCheck) { 
            saveVec.push_back(i);
        }
        
        primeCheck = true;
    }

    // İşlem tamamlandığında %100 olarak göster
    loadingBar(1.0);
    std::cout << std::endl;

    return saveVec;
}

/**
 * @brief 
 * 
 * @return std::vector<uint32_t> *
 */
std::vector<uint32_t>* cropPrimeList(const std::vector<uint32_t>& plist, uint32_t maxValue) {
    std::vector<uint32_t>* retVec = new std::vector<uint32_t>;

    if(plist.back() < maxValue){
        std::cerr << "The Control list is not enought for calculation" << std::endl;
        return NULL;
    }

    for (uint32_t prime : plist) {
        
        if (prime > maxValue) { 
            break; 
        }

        retVec->push_back(prime);
    }

    return retVec;
}
