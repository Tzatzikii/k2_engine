#ifndef K2_ENGINE_BASIC_ALGORITHMS_HPP_
#define K2_ENGINE_BASIC_ALGORITHMS_HPP_

#include "matrix4.hpp"
#include "vector4.hpp"
namespace k2_math{

template <typename T>
inline Vec4<T> intersect_h(const Vec4<T>& v0, const Vec4<T>& v1, float line){

        float dx = v0.get_x() - v1.get_x();
        float dy = v0.get_y() - v1.get_y();
        float dz = v0.get_z() - v1.get_z();
        float delta_z = v0.get_z() - line;
        float delta_y = delta_z*(dy/dz);
        float delta_x = delta_z*(dx/dz);
        return Vec4<T>(v0.get_x()-delta_x, v1.get_y(), delta_z);
}

}
#endif