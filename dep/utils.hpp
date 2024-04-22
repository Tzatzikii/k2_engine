/**
 * @file utils.hpp
 * @author Klemm Gábor - Neptun: H8XK58
 * @brief A fájl neve igazából magáért beszél, csak gyakran használt inline függvények
 *        egy helyen, nincs hozzátartozó utils.cpp file
 *
 * @version 0.1
 * @date 2024-03-08
 * 
 * 
 */
#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cmath>

namespace k2_engine{

//#define DEBUG

/**
 * @brief Felcseréli a két paraméterét
 * 
 * @tparam T - Igazából bármit fel lehet vele cserélni
 * @param A - Felcseréli B-vel
 * @param B - Felcseréli A-val
 */
template <typename T>
inline void swap(T& A, T& B){

        T C = A;
        A = B;
        B = C;

}
template <typename T>
inline T max_3(T A, T B, T C){
        T max = std::max(A, B);
        max = std::max(B, C);
        return max;
}

/**
 * @brief Főleg két valós, vagy két egész szám korlátozására
 *        hoztam létre
 * 
 * @tparam T - double, vagy int, de lehet saját osztály is, ha
 *         megfelelően vannak rá definiálva az összehasonlítások
 * @param val - Maga az érték
 * @param min - A miniumum korlát, ha a paraméter túllépi, akkor ez
 *              lesz az új értéke
 * @param max - A maximum korlát, ha a paraméter túllépi, akkor ez
 *              lesz az új értéke
 */
template <typename T>
inline void clamp(T& val, T min, T max){

        if(val < min) val = min;
        else if(val > max) val = max;

}
/**
 * @brief Egy adott értékről megmondja, hogy a megadott korlátokon
 *        belül van -e
 * 
 * @param max - Egy valós maximum
 * @param min - Egy valós minimum
 * @param val - Egy valós szám
 * @return true  ,ha a korlátok között van
 * @return false ,ha nincs a korlátok között
 */
inline bool boundary(double min, double max, double val){

        return (val >= min && val <= max);

}


/**
 * @brief Két dimenzióra kiterjesztett Pythagoras-tétel
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return double 
 */
template <typename T>
inline double pyth2d(const T a, T b){return sqrt(a*a + b*b);}

/**
 * @brief Három dimenzióra kiterjesztett Pythagoras-tétel
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @param c 
 * @return double 
 */
template <typename T>
inline double pyth3d(const T a, T b, T c){return sqrt(a*a + b*b + c*c);}

} // namespace k2_engine

#endif // UTILS_HPP_