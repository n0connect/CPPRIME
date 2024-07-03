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
 * @return std::vector<mpz_class> Bulunan asal sayıların vektörü
 */
std::vector<mpz_class> calculateBetween(mpz_class start, mpz_class stop, const std::vector<mpz_class>& plist) {
    bool primeCheck = true;
    //uint32_t marginErr = 10;
    
    mpz_class sqrtStop;
    mpz_sqrt(sqrtStop.get_mpz_t(), stop.get_mpz_t());

    // Asal sayı listesini kırp [Disabled]
    //std::vector<mpz_class> primeList = *cropPrimeList(plist, sqrtStop + marginErr);
    std::vector<mpz_class> saveVec;

    // Başlangıç değerinin tek olup olmadığını kontrol et
    if (mpz_even_p(start.get_mpz_t())) {
        //mtx.lock();
        std::clog << "Start number is not odd, incrementing by 1" << std::endl;
        start++;
        //mtx.unlock();
    }

    // İşlem çubuğu gösterimi
    //mtx.lock();
    std::cout << "Calculating numbers between " << start << " and " << stop << "\n";
    //mtx.unlock();

    for (mpz_class i = start; i < stop; i += 2) {
        
        mpz_class sqrtNum;
        mpz_sqrt(sqrtNum.get_mpz_t(), i.get_mpz_t());
        primeCheck = true;

        for (const auto& prime : plist) {
            
            if (mpz_divisible_p(i.get_mpz_t(), prime.get_mpz_t()))
            { 
                primeCheck = false; 
                break;
            
            }
            //else if (sqrtNum < prime)
            //
            //{
            //    break;
            //}
        }

        if (primeCheck) { 
            saveVec.push_back(i);
        }
    }

    // Vektördeki tekrar eden elemanları kaldır ve vektörü küçükten büyüğe sırala
    //std::sort(saveVec.begin(), saveVec.end());
    //auto last = std::unique(saveVec.begin(), saveVec.end());
    //saveVec.erase(last, saveVec.end());

    return saveVec;
}

/**
 * @brief Aralık listesi içerisindeki start ve stop değerlerine göre asal sayıları tespit eder.
 * 
 * @param ranges Aralık listesindeki her bir ikili eleman (start, stop) 
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @return std::vector<mpz_class> Bulunan asal sayıların vektörü
 */
std::vector<mpz_class> calculateForRanges(const std::vector<std::pair<mpz_class, mpz_class>>& ranges, const std::vector<mpz_class>& plist) {
    std::vector<mpz_class> saveVec;
    
    for (const auto& range : ranges) {
        std::vector<mpz_class> partialResults = calculateBetween(range.first, range.second, plist);
        saveVec.insert(saveVec.end(), partialResults.begin(), partialResults.end());
    }

    // İşlem tamamlandığında %100 olarak göster
    mtx.lock();
    loadingBar(1.0);
    std::cout << std::endl;
    mtx.unlock();

    return saveVec;
}

/**
 * @brief Start ve Stop değerleri arasında paralel olarak asal sayıları hesaplar.
 * 
 * @param start Başlangıç değeri
 * @param stop Bitiş değeri
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @param numThreads Kullanılacak thread sayısı
 * @param chunkCount Her bir thread için işlenecek aralık sayısı
 * @param chunkRange Her bir işlenecek aralığın büyüklüğü
 * @return std::vector<mpz_class> Bulunan asal sayıların vektörü
 */
std::vector<mpz_class> parallelPrimeCalculation(mpz_class start, mpz_class stop, const std::vector<mpz_class>& plist, uint32_t numThreads, uint32_t chunkCount, mpz_class chunkRange) {
    std::vector<std::thread> threads;
    std::vector<std::vector<mpz_class>> results(numThreads);

    // Her bir thread için aralıkları hazırlayın
    std::vector<std::vector<std::pair<mpz_class, mpz_class>>> threadRanges(numThreads);

    for (uint32_t i = 0; i < numThreads; ++i) {
        for (uint32_t j = 0; j < chunkCount; ++j) {
            mpz_class rangeStart = start + (i + j * numThreads) * chunkRange;

            if (mpz_even_p(rangeStart.get_mpz_t())) {
                rangeStart++;
            }

            mpz_class rangeStop = rangeStart + chunkRange;
            if (rangeStop > stop) {
                rangeStop = stop;
            }

            threadRanges[i].emplace_back(rangeStart, rangeStop);
            
            /**************** NOT GOOD *****************/
            // BU KISMI MUTLAKA OPTIMIZE ETMELIYIM.
            // İdarelik bir çözüm buldum.
            if(numThreads-1 <= i && chunkCount-1 <= j){
                threadRanges[i].emplace_back(rangeStop, stop);
            }
        }
    }

    //for(const auto &num : threadRanges){
    //    
    //    for(const auto &numx : num){
    //        std::cout << "("<< numx.first << ", " << numx.second << ")" << ", ";
    //    } std::cout << "\n\n";
    //}

    //exit(1);

    //for(uint32_t i = 0; i < threadRanges.size(); ++i){
    //   std::cout << threadRanges[i].size() << ", ";
    //   exit(1);
    //}

    for (uint32_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([&, i] {
            results[i] = calculateForRanges(threadRanges[i], plist);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::vector<mpz_class> finalResults;
    for (const auto& result : results) {
        finalResults.insert(finalResults.end(), result.begin(), result.end());
    }

    std::sort(finalResults.begin(), finalResults.end());
    auto last = std::unique(finalResults.begin(), finalResults.end());
    finalResults.erase(last, finalResults.end());

    std::cout << " !- Paralize calculation end -! " << std::endl;
    std::cout << std::endl;

    return finalResults;
}

/**
 * @brief Asal sayı listesini belirtilen maksimum değere kadar kırpar.
 * 
 * @param plist Asal sayı listesi
 * @param maxValue Maksimum değer
 * @return std::vector<mpz_class>* Kırpılmış asal sayı listesi
 */
std::vector<mpz_class>* cropPrimeList(const std::vector<mpz_class>& plist, mpz_class maxValue) {
    std::vector<mpz_class>* retVec = new std::vector<mpz_class>;

    if (plist.back() < maxValue) {
        std::cerr << "The control list is not enough for calculation" << std::endl;
        return nullptr;
    }

    for (const auto& prime : plist) {
        if (prime > maxValue) {
            break;
        }
        retVec->push_back(prime);
    }

    return retVec;
}
