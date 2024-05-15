#include "shapes.hpp"


namespace k2_engine{

using namespace k2_math;

using VecF = k2_math::Vec4<float>;
using VecRGB = k2_math::Vec4<unsigned char>;
using MatF = k2_math::Mat4<float>;
constexpr float pi = 3.1415926535f; 
void Shape::calculate_centre(){
        Vec4<float> centre;
        for(Triangle t : components){
                centre += VecF((t.get_v0().get_pos() + t.get_v1().get_pos() + t.get_v2().get_pos())/3);
        }
        centre/=components.size();
}

void Shape::transform(MatF transformation_matrix){
        for(Triangle& t : components){
                t.transform(transformation_matrix);
        }
}
Shape Shape::Quad(VecF centre, VecF orientation, float size, VecRGB color, float opacity){
                Shape quad;
                Triangle t0(VecF(-size/2, -size/2, 0), VecF(-size/2, size/2, 0), VecF(size/2, -size/2, 0), color);
                Triangle t1(VecF(size/2, size/2, 0), VecF(-size/2, size/2, 0), VecF(size/2, -size/2, 0), color);
                t0.transform(MatF::translation(centre)*MatF::rotation(orientation));
                t1.transform(MatF::translation(centre)*MatF::rotation(orientation));

                quad.components.push_back(t0);
                quad.components.push_back(t1);
                return quad;
                
}

Shape Shape::Cube(VecF centre, VecF orientation, float size, VecRGB color, float opacity){
        Shape cube;
        cube.centre = centre;
        Shape quad = Shape::Quad(VecF(0, 0, 0), orientation, size, color, opacity);

#define INSERT_QUAD cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre+VecF(0, 0, size/2)));
        INSERT_QUAD
        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        INSERT_QUAD
        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        INSERT_QUAD
        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        INSERT_QUAD

        return cube;

}


}//namespace