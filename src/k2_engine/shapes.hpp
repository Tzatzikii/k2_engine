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
        Shape(float opacity): opacity(opacity){}
        Shape(const Shape& shape): components(shape.components), centre(shape.centre), opacity(shape.opacity){}
        virtual std::vector<Triangle> get_components() const { return components; }
        void transform(k2_math::Mat4<float> transformation_matrix);
};

class Quad : public Shape{
public:
        Quad(const k2_math::Vec4<float> A, k2_math::Vec4<float> B, k2_math::Vec4<float> C, k2_math::Vec4<float> D, float opacity = 0)
                : Shape(opacity){
                        components.push_back(Triangle(A, B, C));
                        components.push_back(Triangle(C, D, A));
                }
};
}//namespace
#endif //K2_ENGINE_SHAPES_HPP_