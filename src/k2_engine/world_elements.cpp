#include "world_elements.hpp"

namespace k2_engine{

using namespace k2_math;
void Camera::translate(Vec4<float> v){
        pos +=  k2_math::Mat4<float>::rotation(0, rot.get_y(), 0) * v;
}
void Camera::translate(float dx, float dy, float dz){
        Vec4<float> v(dx, dy, dz);
        translate(v);
}
void Camera::tick(float groundy){
        translate(velocity);
        if(pos.get_y() < groundy) pos.set_y(groundy);
        if(pos.get_y() >= groundy && pos.get_y() < groundy+0.1){
                if(velocity.get_x() > 0){
                        if(!(velocity.get_x() - 0.1 < 0)) velocity-=Vec4<float>(-1,0,0);
                        else velocity.set_x(0);
                }
                if(velocity.get_x() < 0){
                        if(!(velocity.get_x() + 0.1 > 0)) velocity+=Vec4<float>(1,0,0);
                        else velocity.set_x(0);
                }
                if(velocity.get_z() > 0){
                        if(!(velocity.get_z() - 0.1 < 0)) velocity-=Vec4<float>(0, 0, -1);
                        else velocity.set_z(0);
                }
                if(velocity.get_z() < 0){
                        if((!velocity.get_z() + 0.1 > 0)) velocity+=Vec4<float>(0,0,1);
                        else velocity.set_z(0);
                }
        }
}
void Camera::move(float dx, float dy, float dz){
        velocity += Vec4<float>(dx, dy, dz);
}

}