#include "shapes.hpp"


namespace k2_engine{

using namespace k2_math;

using VecF = k2_math::Vec4<float>;
using VecRGB = k2_math::Vec4<unsigned char>;
using MatF = k2_math::Mat4<float>;
constexpr float pi = 3.1415926535f; 


void Shape::transform(MatF transformation_matrix){
        for(Triangle& t : components){
                t.transform(transformation_matrix);
        }
}
Shape Shape::Quad(VecF centre, VecF orientation, float size, VecRGB color, float opacity){
                Shape quad;
                quad.centre = centre;
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


        quad.transform(MatF::translation(centre+VecF(0, 0, size/2)));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre)*MatF::rotation_y(pi/2)*MatF::translation(-centre));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre)*MatF::rotation_z(pi/2)*MatF::translation(-centre));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        quad.transform(MatF::translation(centre)*MatF::rotation_z(pi)*MatF::translation(-centre));
        cube.components.insert(cube.components.end(), quad.components.begin(), quad.components.end());

        return cube;

}

std::ofstream& operator<<(std::ofstream& os, const Shape& shape){
        os<<shape.get_components().size();
        for(Triangle t : shape.components){
                os<<t;
        }
        return os;
}
std::ifstream& operator>>(std::ifstream& is, Shape& shape){
        size_t components_length;
        is>>components_length;
        for(size_t i = 0; i < components_length; ++i){
                Triangle tmp;
                is>>tmp;
                shape.components.push_back(tmp);
        }
        return is;
}

} // namespace