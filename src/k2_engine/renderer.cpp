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
}
void Renderer::project(){
       Mat4<float> proj_mtx = Mat4<float>::projection(Vec4<float>((float)window_width, (float)window_height, scene->get_camera().get_radius())); 
       for( Triangle& t : wiremesh){
                Triangle cpy(t);
                cpy.transform(proj_mtx);

                Mat4<float> fw_divide = Mat4<float>()/cpy.get_v0().get_pos().get_z();
                cpy.ref_v0().set_pos(fw_divide*cpy.get_v0().get_pos());
                
                fw_divide = Mat4<float>()/cpy.get_v1().get_pos().get_z();
                cpy.ref_v1().set_pos(fw_divide*cpy.get_v1().get_pos());

                fw_divide = Mat4<float>()/cpy.get_v2().get_pos().get_z();
                cpy.ref_v2().set_pos(fw_divide*cpy.get_v2().get_pos());

                if(boundary(0, window_width-1, cpy.get_v0().get_pos().get_x()) && boundary(0, window_height-1, cpy.get_v0().get_pos().get_y()))
                        output_buffer.set_buffer(cpy.get_v0().get_pos().get_x(), cpy.get_v0().get_pos().get_y(), '#');
                
                if(boundary(0, window_width-1, cpy.get_v1().get_pos().get_x()) && boundary(0, window_height-1, cpy.get_v1().get_pos().get_y()))
                        output_buffer.set_buffer(cpy.get_v1().get_pos().get_x(), cpy.get_v1().get_pos().get_y(), '#');

                if(boundary(0, window_width-1, cpy.get_v2().get_pos().get_x()) && boundary(0, window_height-1 ,cpy.get_v2().get_pos().get_y()))
                        output_buffer.set_buffer(cpy.get_v2().get_pos().get_x(), cpy.get_v2().get_pos().get_y(), '#');
               
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