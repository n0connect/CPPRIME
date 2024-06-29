/* primealgorithm.h */

#ifndef PRIMEALGORITHM_H
#define PRIMEALGORITHM_H

#include <vector>
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
 * @return std::vector<uint32_t> Bulunan asal sayıların vektörü
 */
std::vector<uint32_t> calculateBetween(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist);

/**
 * @brief Start ve Stop değerleri arasında paralel olarak asal sayıları hesaplar.
 * 
 * @param start Başlangıç değeri
 * @param stop Bitiş değeri
 * @param plist Daha önce hesaplanmış asal sayılar listesi
 * @param numThreads Kullanılacak thread sayısı
 * @return std::vector<uint32_t> Bulunan asal sayıların vektörü
 */
std::vector<uint32_t> parallelPrimeCalculation(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist, uint32_t numThreads);
 
/**
 * @brief Asal sayı listesini belirtilen maksimum değere kadar kırpar.
 * 
 * @param plist Asal sayı listesi
 * @param maxValue Maksimum değer
 * @return std::vector<uint32_t>* Kırpılmış asal sayı listesi
 */
std::vector<uint32_t>* cropPrimeList(const std::vector<uint32_t>& plist, uint32_t maxValue);

#endif