#include "shapes.hpp"


namespace k2_engine{

using namespace k2_math;

void Shape::calculate_centre(){
        Vec4<float> centre;
        for(Triangle t : components){
                centre += Vec4<float>((t.get_v0().get_pos() + t.get_v1().get_pos() + t.get_v2().get_pos())/3);
        }
        centre/=components.size();
}

void Shape::transform(Mat4<float> transformation_matrix){
        for(Triangle& t : components){
                t.transform(transformation_matrix);
        }
}
Shape Shape::Quad(k2_math::Vec4<float> A, k2_math::Vec4<float> B, k2_math::Vec4<float> C,
k2_math::Vec4<float> D, float opacity){
                Shape quad;
                quad.components.push_back(Triangle(A, B, C));
                quad.components.push_back(Triangle(C, D, A));
                return quad;
                
}


}//namespace