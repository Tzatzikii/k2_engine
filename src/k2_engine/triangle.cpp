#include "triangle.hpp"

namespace k2_engine{

using namespace k2_math;

void Triangle::transform(Mat4<float> transformation_matrix){
        v0.set_pos( transformation_matrix*v0.get_pos() );
        v1.set_pos( transformation_matrix*v1.get_pos() );
        v2.set_pos( transformation_matrix*v2.get_pos() );
}
}