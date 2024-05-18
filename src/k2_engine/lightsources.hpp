/**
 * @file lightsources.hpp
 * @author Klemm Gábor (H8XK58)
 * @brief A fényforrások megvalósításánal lehetéségét fent tartja, nincs használva
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef K2_ENGINE_LIGHTSOURCES_HPP_
#define K2_ENGINE_LIGHTSOURCES_HPP_
#include "../k2_math/matrix4.hpp"
#include "world_elements.hpp"

namespace k2_engine{

class AmbientLight : public LightSource{
public:
        void transform(k2_math::Mat4<float> mtx);
        void write(std::ofstream& os);
}; 

class DirectionalLight : public LightSource{
        k2_math::Vec4<float> dir;

public:
        DirectionalLight(k2_math::Vec4<float> dir)
                : dir(dir){ dir.set_w(0); }
        void transform(k2_math::Mat4<float> mtx);
        void write(std::ofstream& os);

};

class SphericalLight{
        float radius;
        k2_math::Vec4<float> pos;

public:
        SphericalLight(k2_math::Vec4<float> pos, float radius)
                : pos(pos), radius(radius){}

        SphericalLight(float x, float y, float z, float radius)
                : pos(k2_math::Vec4<float>(x, y, z)), radius(radius){}
        void transform(k2_math::Mat4<float> mtx);
        k2_math::Vec4<float>& ref_pos(){ return pos; } 
        void write(std::ofstream& os);
};

}//namespace
#endif //K2_ENGINE_LIGHTSOURCES_HPP_