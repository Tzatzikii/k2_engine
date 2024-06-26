#ifndef K2_ENGINE_TRIANGLE_HPP
#define K2_ENGINE_TRIANGLE_HPP

#include "../k2_math/vector4.hpp"
#include "../k2_math/matrix4.hpp"
#include "vertex.hpp"
#include <fstream>
namespace k2_engine{
class Triangle{
        Vertex v0;
        Vertex v1;
        Vertex v2;
        
public:
        Triangle() : v0(Vertex()), v1(Vertex()), v2(Vertex()){}
        Triangle(const k2_math::Vec4<float> A, k2_math::Vec4<float> B, k2_math::Vec4<float> C, k2_math::Vec4<unsigned char> color)
                : v0(Vertex(A, color)), v1(Vertex(B, color)), v2(Vertex(C, color)){}
        Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
                : v0(v0), v1(v1), v2(v2){}
        Triangle(const Triangle& t)
                : v0(t.v0), v1(t.v1), v2(t.v2){}   

        Vertex get_v0() const { return v0; }
        Vertex get_v1() const { return v1; }
        Vertex get_v2() const { return v2; }
        Vertex& ref_v0() { return v0; }
        Vertex& ref_v1() { return v1; }
        Vertex& ref_v2() { return v2; }
        void set_v0(const Vertex& new_v0) { v0 = new_v0; }
        void set_v1(const Vertex& new_v1) { v1 = new_v1; }
        void set_v2(const Vertex& new_v2) { v2 = new_v2; }
        void transform(k2_math::Mat4<float> transformation_matrix); 
        friend std::ofstream& operator<<(std::ofstream& os, const Triangle& triangle);
        friend std::ifstream& operator>>(std::ifstream& is, Triangle& triangle);
};

}
#endif