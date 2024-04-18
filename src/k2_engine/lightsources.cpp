#include "lightsources.hpp"

namespace k2_engine{

using namespace k2_math;

void AmbientLight::transform(Mat4<float> m){}

void SphericalLight::transform(Mat4<float> transform_mtx){
       pos = transform_mtx*pos; 
}
void DirectionalLight::transform(Mat4<float> transform_mtx){
        dir = transform_mtx*dir;
} 

}//namespace