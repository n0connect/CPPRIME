/* primealgorithm.h */
#ifndef PRIMEALGORITHM_H
#define PRIMEALGORITHM_H

#include <vector>
#include <gmpxx.h>
#include "primefile.h"

/**
 * @brief KOnsol ekranında bulunacak olan işlem çubuğu.
 * 
 * @param progress 
 */
void loadingBar(double progress);

/**
 * @brief Start ve Stop değerleri arasında bulunan asal sayıları tespit eder.
 * 
 * @param start Başlangıç değeri
 * @param stop Bitiş değeri
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @return std::vector<mpz_class> Bulunan asal sayıların vektörü
 */
std::vector<mpz_class> calculateBetween(mpz_class start, mpz_class stop, const std::vector<mpz_class>& plist);

/**
 * @brief Aralık listesi içerisindeki start ve stop değerlerine göre asal sayıları tespit eder.
 * 
 * @param ranges Aralık listesindeki her bir ikili eleman (start, stop) 
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @return std::vector<mpz_class> Bulunan asal sayıların vektörü
 */
std::vector<mpz_class> calculateForRanges(const std::vector<std::pair<mpz_class, mpz_class>>& ranges, const std::vector<mpz_class>& plist);

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
std::vector<mpz_class> parallelPrimeCalculation(mpz_class start, mpz_class stop, const std::vector<mpz_class>& plist, uint32_t numThreads, uint32_t chunkCount, mpz_class chunkRange);

/**
 * @brief Asal sayı listesini belirtilen maksimum değere kadar kırpar.
 * 
 * @param plist Asal sayı listesi
 * @param maxValue Maksimum değer
 * @return std::vector<mpz_class>* Kırpılmış asal sayı listesi
 */
std::vector<mpz_class>* cropPrimeList(const std::vector<mpz_class>& plist, mpz_class maxValue);

#endif

