/* primealgorithm.cpp */

#include "primealgorithm.h"
#include "primefile.h"

#include <algorithm>
#include <thread>
#include <mutex>
#include <cmath>

// Mutex for thread-safe writing to saveVec
std::mutex mtx;

// Terminalde işlem çubuğu gösterimi
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
 * @param start Başlangıç değeri
 * @param stop Bitiş değeri
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @return std::vector<uint32_t> Bulunan asal sayıların vektörü
 */
std::vector<uint32_t> calculateBetween(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist) {
    bool primeCheck = true;
    uint32_t marginErr = 10;
    
    // Asal sayı listesini kırp
    std::vector<uint32_t> primeList = *cropPrimeList(plist, static_cast<uint32_t>(sqrtf(stop) + marginErr));
    std::vector<uint32_t> saveVec;

    uint32_t total = (stop - start) / 2;
    uint32_t partJob = total / 100;

    // Başlangıç değerinin tek olup olmadığını kontrol et
    if (start % 2 == 0) {
        std::clog << "Start number is not odd, incrementing by 1" << std::endl;
        start++;
    }

    // İşlem çubuğu gösterimi
    std::cout << "Calculating numbers between " << start << " and " << stop << "\n";

    for (uint32_t i = start; i < stop; i += 2) {
        // İşlem çubuğunu güncelle
        //if ((i - start) % partJob == 1) { 
        //    loadingBar(static_cast<double>(i - start) / (stop - start));
        //}

        primeCheck = true;
        for (uint32_t prime : primeList) {
            if (i % prime == 0) { 
                primeCheck = false; 
                break; 
            }
        }

        if (primeCheck) { 
            saveVec.push_back(i);
        }
    }

    // Vektördeki tekrar eden elemanları kaldır ve vektörü küçükten büyüğe sırala
    std::sort(saveVec.begin(), saveVec.end());
    auto last = std::unique(saveVec.begin(), saveVec.end());
    saveVec.erase(last, saveVec.end());

    // İşlem tamamlandığında %100 olarak göster
    loadingBar(1.0);
    std::cout << std::endl;

    return saveVec;
}

/**
 * @brief Start ve Stop değerleri arasında paralel olarak asal sayıları hesaplar.
 * 
 * @param start Başlangıç değeri
 * @param stop Bitiş değeri
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @param numThreads Kullanılacak thread sayısı
 */
std::vector<uint32_t> parallelPrimeCalculation(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist, uint32_t numThreads) {
    uint32_t range = (stop - start) / numThreads;
    std::vector<std::thread> threads;
    std::vector<std::vector<uint32_t>> results(numThreads);

    for (uint32_t i = 0; i < numThreads; ++i) {
        uint32_t rangeStart = start + i * range;
        uint32_t rangeStop = (i == numThreads - 1) ? stop : rangeStart + range;

        // Her thread'in başlangıç değerinin tek olup olmadığını kontrol et
        if (rangeStart % 2 == 0) {
            std::clog << "Thread " << i << ": Start number is not odd, incrementing by 1" << std::endl;
            rangeStart++;
        }

        // Her thread'i başlat ve hesaplama yap
        threads.emplace_back([&, rangeStart, rangeStop, i] {
            results[i] = calculateBetween(rangeStart, rangeStop, plist);
        });
    }

    // Thread'lerin tamamlanmasını bekle
    for (auto& thread : threads) {
        thread.join();
    }

    // Sonuçları birleştir
    std::vector<uint32_t> finalResults;
    for (const auto& result : results) {
        finalResults.insert(finalResults.end(), result.begin(), result.end());
    }

    // Tekrar eden elemanları kaldır ve sonuçları sırala
    std::sort(finalResults.begin(), finalResults.end());
    auto last = std::unique(finalResults.begin(), finalResults.end());
    finalResults.erase(last, finalResults.end());

    // Sonuçları yazdır veya kaydet
    std::cout << " !- Paralize calculation end -! " << std::endl;
    std::cout << std::endl;

    return finalResults;
}

/**
 * @brief Asal sayı listesini belirtilen maksimum değere kadar kırpar.
 * 
 * @param plist Asal sayı listesi
 * @param maxValue Maksimum değer
 * @return std::vector<uint32_t>* Kırpılmış asal sayı listesi
 */
std::vector<uint32_t>* cropPrimeList(const std::vector<uint32_t>& plist, uint32_t maxValue) {
    std::vector<uint32_t>* retVec = new std::vector<uint32_t>;

    if (plist.back() < maxValue) {
        std::cerr << "The control list is not enough for calculation" << std::endl;
        return nullptr;
    }

    for (uint32_t prime : plist) {
        if (prime > maxValue) {
            break;
        }
        retVec->push_back(prime);
    }

    return retVec;
}
