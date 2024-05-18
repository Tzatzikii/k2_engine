#include "lightsources.hpp"

namespace k2_engine{

using namespace k2_math;

void AmbientLight::transform(Mat4<float> m){}
void AmbientLight::write(std::ofstream& os){}
void SphericalLight::transform(Mat4<float> transform_mtx){
       pos = transform_mtx*pos; 
}
void SphericalLight::write(std::ofstream& os){}
void DirectionalLight::transform(Mat4<float> transform_mtx){
        dir = transform_mtx*dir;
}
void DirectionalLight::write(std::ofstream& os){}
        
}//namespace