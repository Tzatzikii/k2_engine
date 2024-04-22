#include "renderer.hpp"

namespace k2_engine{

using namespace k2_math;

void Renderer::extract_wiremesh(){
        for(const Object* const obj : scene->get_objects()){
                obj->get_shape();
                for(Triangle t : obj->get_shape().get_components()){
                        wiremesh.push_back(t);
                }
        }

}

void Renderer::illuminate(){

}
void Renderer::view_transform(){
        const Camera& cam = scene->get_camera(); 
        Mat4<float> inv_cam_pos_mtx = Mat4<float>::inverse_translation(Mat4<float>::translation(cam.get_pos()));
        Mat4<float> inv_cam_rot_mtx = Mat4<float>::inverse_rotation(Mat4<float>::rotation(cam.get_rot()));
        Mat4<float> inv_transform = inv_cam_rot_mtx*inv_cam_pos_mtx;
        for(Triangle& t : wiremesh){
                t.transform(inv_transform);
        }

}
void Renderer::cull(){
        float screen_z = scene->get_camera().get_radius();

        for( auto iter = wiremesh.begin(); iter != wiremesh.end(); iter++){
                Triangle& t = *iter;
                //sorbarendezés az alapján, hogy melyik lóg ki
                Vertex* varr[3] = { &t.ref_v0(), &t.ref_v1(), &t.ref_v2() };

                if( varr[0]->get_pos().get_z() > screen_z ){
                        if(varr[1]->get_pos().get_z() < screen_z ) swap(varr[0], varr[1]);
                        else if(varr[2]->get_pos().get_z() < screen_z ) swap(varr[0], varr[1]);
                }
                if( varr[2]->get_pos().get_z() < screen_z ) swap(varr[1], varr[2]);

        }        
}
void Renderer::project(){
        Mat4<float> proj_mtx = Mat4<float>::projection(Vec4<float>((float)window_width, (float)window_height, scene->get_camera().get_radius())); 
        for( Triangle& t : wiremesh){
                t.transform(proj_mtx);

                Mat4<float> fw_divide = Mat4<float>()/t.get_v0().get_pos().get_z();
                t.ref_v0().set_pos(fw_divide*t.get_v0().get_pos());
                
                fw_divide = Mat4<float>()/t.get_v1().get_pos().get_z();
                t.ref_v1().set_pos(fw_divide*t.get_v1().get_pos());

                fw_divide = Mat4<float>()/t.get_v2().get_pos().get_z();
                t.ref_v2().set_pos(fw_divide*t.get_v2().get_pos());
        }
}
void Renderer::draw(){
        output_buffer.push_to_stdout();
        wiremesh.clear();
        output_buffer.clear_buffer();
}

void Renderer::render(){
        extract_wiremesh();
        view_transform();
        project();
        draw();
}
}//namespace