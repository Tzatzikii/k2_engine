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
typedef long int intptr_t;
#include <chrono>
namespace k2_engine{

void start_main();
       
void init_console();

void restore_console();

template <typename T>
inline float get_delta(std::chrono::time_point<T> prev){
        std::chrono::seconds s;
        std::chrono::time_point<T> curr = std::chrono::high_resolution_clock::now();
        auto diff = curr - prev;
        float delta = diff.count()/s.count();
        return delta;
}
void main_loop();

} // namespace k2


#endif // K2_ENGINE_ENGINE_MAIN_HPP_