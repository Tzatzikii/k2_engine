#ifndef K2_ENGINE_ENGINE_MAIN_HPP_
#define K2_ENGINE_ENGINE_MAIN_HPP_

#include "../../dep/output.hpp"
#include "../k2_math/vector4.hpp"
#include "../k2_math/matrix4.hpp"
#include "gamespace.hpp"
#include "renderer.hpp"
#include <vector>
#include <cstring>

namespace k2_engine{

void start_main();
       
void init_console();

void restore_console();
        
void main_loop();

} // namespace k2


#endif // K2_ENGINE_ENGINE_MAIN_HPP_