#include "shapes.hpp"


namespace k2_engine{

using namespace k2_math;

typedef k2_math::Vec4<float> vecf;
typedef k2_math::Mat4<float> matf;
constexpr float pi = 3.141592653;
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

Shape Shape::Cube(k2_math::Vec4<float> c, float s){
        Shape cube;
        Shape quad0 = Shape::Quad(vecf(0, s/2, s/2),vecf(0, -s/2, s/2),vecf(0, -s/2, -s/2), vecf(0, s/2, -s/2));
        Shape quad1(quad0), quad2(quad0), quad3(quad0), quad4(quad0), quad5(quad0);
        quad0.transform(matf::translation(c + vecf(s/2, 0, 0))); // back
        quad1.transform(matf::translation(c + vecf(-s/2, 0, 0))); // front
        quad2.transform(matf::translation(c + vecf(0, 0, s/2))*matf::rotation_y(pi/2));
        quad3.transform(matf::translation(c + vecf(0, 0, -s/2))*matf::rotation_y(-pi/2));
        quad4.transform(matf::translation(c + vecf(0, s/2, 0))*matf::rotation_z(pi/2));
        quad5.transform(matf::translation(c+ vecf(0, -s/2, 0))*matf::rotation_z(-pi/2));
        cube.components.insert(cube.components.begin(), quad0.components.begin(), quad0.components.end());
        cube.components.insert(cube.components.begin(), quad1.components.begin(), quad1.components.end());
        cube.components.insert(cube.components.begin(), quad2.components.begin(), quad2.components.end());
        cube.components.insert(cube.components.begin(), quad3.components.begin(), quad3.components.end());
        cube.components.insert(cube.components.begin(), quad4.components.begin(), quad4.components.end());
        cube.components.insert(cube.components.begin(), quad5.components.begin(), quad5.components.end());
        return cube;

}


}//namespace