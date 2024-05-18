#include "triangle.hpp"

namespace k2_engine{

using namespace k2_math;

void Triangle::transform(Mat4<float> transformation_matrix){
        v0.set_pos( transformation_matrix*v0.get_pos() );
        v1.set_pos( transformation_matrix*v1.get_pos() );
        v2.set_pos( transformation_matrix*v2.get_pos() );
}
std::ofstream& operator<<(std::ofstream& os, const Triangle& triangle){
        os<<triangle.v0<<triangle.v1<<triangle.v2;
        return os;
}
std::ifstream& operator>>(std::ifstream& is, Triangle& triangle){
        is>>triangle.v0>>triangle.v1>>triangle.v2;
        return is;
}
}