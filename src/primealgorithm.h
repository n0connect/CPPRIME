/* primealgorithm.h */

#ifndef PRIMEALGORITHM_H
#define PRIMEALGORITHM_H

#include <iostream>
#include <vector>
#include <math.h>
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
 * @param start 
 * @param stop 
 * @param plist 
 * @return std::vector<uint32_t> 
 */
std::vector<uint32_t> calculateBetween(uint32_t start, uint32_t stop, const std::vector<uint32_t>& plist);

/**
 * @brief 
 * 
 * @return std::vector<uint32_t> *
 */
std::vector<uint32_t> *cropPrimeList(const std::vector<uint32_t> &plist, uint32_t maxValue);

#endif