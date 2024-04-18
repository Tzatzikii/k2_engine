#ifndef K2_ENGINE_LIGHTSOURCES_HPP_
#define K2_ENGINE_LIGHTSOURCES_HPP_
#include "../k2_math/matrix4.hpp"
#include "world_elements.hpp"

namespace k2_engine{

class AmbientLight : public LightSource{
public:
        void transform(k2_math::Mat4<float> mtx);
}; 

class DirectionalLight : public LightSource{
        k2_math::Vec4<float> dir;

public:
        DirectionalLight(k2_math::Vec4<float> dir)
                : dir(dir){ dir.set_w(0); }
        void transform(k2_math::Mat4<float> mtx);

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
};

}//namespace
#endif //K2_ENGINE_LIGHTSOURCES_HPP_