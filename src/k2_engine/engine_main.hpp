/**
 * @file engine_main.hpp
 * @author Klemm Gábor (H8XK58)
 * @brief Magát a motort fogja össze és kezeli le/indítja el a fő eseményeket
 * @version 0.1
 * @date 2024-05-17
 * 
 * 
 */
#ifndef K2_ENGINE_ENGINE_MAIN_HPP_
#define K2_ENGINE_ENGINE_MAIN_HPP_

#include "../../dep/output.hpp"
#include "../k2_math/vector4.hpp"
#include "../k2_math/matrix4.hpp"
#include "input_handler.hpp"
#include "gamespace.hpp"
#include "renderer.hpp"
#include "scene_creator/scene.hpp"
#include "menu.hpp"
#include <vector>
#include <cstring>
#include <iomanip>
#include <algorithm>
typedef long int intptr_t; // valami miatt a chrono-ban összeakadtak a define-k és nincs definiálva
                           // ezért manuálisan definiáltom kellett, hogy leforduljon a header
#include <chrono>
namespace k2_engine{

/**
 * @brief A CPORTA makró hiányában ez fut ((((tehát a normális program))))
 */
void start_main();

/**
 * @brief A konzolt inicializálja "grafikus" módba
 */
void init_console();

/**
 * @brief A konzolt visszainicializálja konzol módba
 */
void restore_console();

/**
 * @brief meghatároz egy futási deltát, hogy lehessen normalizálni
 *        a tickeket
 * 
 * @tparam T nem kell megadni, azért van, hogy ne kelljen a time_point típusát
 *         minden alkalommal kiírni
 * @param prev előző time point amiből a deltát számítja
 * @return float delta
 */
template <typename T>
inline float get_delta(std::chrono::time_point<T> prev){
        std::chrono::nanoseconds s(1000000000);
        std::chrono::time_point<T> curr = std::chrono::high_resolution_clock::now();
        auto diff = curr - prev;
        outp::Cursor::move(162, 0);
        //std::cout <<"FPS: " << s.count()/diff.count();
        float delta = diff.count();
        return delta;
}

/**
 * @brief maga a fő loop
 * TODO jobb megoldást találni, mint a menübe extern-ként betenni
 * Eredetileg a start_main hívta
 * 
 */
void main_loop(GameSpace scene);

} // namespace k2


#endif // K2_ENGINE_ENGINE_MAIN_HPP_