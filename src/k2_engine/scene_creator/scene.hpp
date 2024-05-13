#ifndef k2_ENGINE_SCENE_CREATOR_SCENE_HPP_
#define k2_ENGINE_SCENE_CREATOR_SCENE_HPP_

#include "../shapes.hpp"
#include "../input_handler.hpp"
#include "../gamespace.hpp"
#include "../lightsources.hpp"
#include "../world_elements.hpp"
#include "../../k2_math/vector4.hpp"
#include <cstring>
using VecF = k2_math::Vec4<float>;
using VecRGB = k2_math::Vec4<unsigned char>;
k2_engine::GameSpace scene_creator();
k2_engine::InputHandler scene_binds(k2_engine::GameSpace&);
#endif