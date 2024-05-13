#ifndef K2_ENGINE_SHAPES_HPP_
#define K2_ENGINE_SHAPES_HPP_
#include "triangle.hpp"
namespace k2_engine{

class Shape{
protected:
        std::vector<Triangle> components;
        k2_math::Vec4<float> centre;
        float opacity; 
        void calculate_centre();

public:
        std::vector<Triangle> get_components() const { return components; }
        void transform(k2_math::Mat4<float> transformation_matrix);

        static Shape Quad(k2_math::Vec4<float> centre, k2_math::Vec4<float> orientation, float size, k2_math::Vec4<unsigned char> color = {255, 255, 255}, float opacity = 1); 
        static Shape Cube(k2_math::Vec4<float> centre, k2_math::Vec4<float> orientation, float size, k2_math::Vec4<unsigned char> color = {255, 255, 255}, float opacity = 1);
};

}//namespace
#endif //K2_ENGINE_SHAPES_HPP_