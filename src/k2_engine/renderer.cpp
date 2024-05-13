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
        Mat4<float> rot_x = Mat4<float>::rotation_x(cam.get_rot().get_x());
        Mat4<float> rot_y = Mat4<float>::rotation_y(cam.get_rot().get_y());
        Mat4<float> inv_cam_rot_mtx = Mat4<float>::inverse_rotation(rot_y*rot_x);
        Mat4<float> inv_transform = inv_cam_rot_mtx*inv_cam_pos_mtx;
        for(Triangle& t : wiremesh){
                t.transform(inv_transform);
        }

}



void Renderer::cull(){
        float screen_z = scene->get_camera().get_radius();
        std::vector<Triangle> new_triangles;
        for(int i = 0; i < wiremesh.size(); i++){
                Triangle& t = wiremesh[i];
                //sorbarendezés az alapján, hogy melyik lóg ki
                Vertex varr[3] = { t.ref_v0(), t.ref_v1(), t.ref_v2() };
                if(varr[0].get_pos().get_z() <= 0 && varr[1].get_pos().get_z() <= 0 && varr[2].get_pos().get_z() <= 0){
                        wiremesh.erase(wiremesh.begin() + i) ;
                        i--;
                        continue;
                }
                else if(varr[0].get_pos().get_z() > 0 && varr[1].get_pos().get_z() > 0 && varr[2].get_pos().get_z() > 0) continue;
                if( varr[0].get_pos().get_z() > 0 ){
                        if(varr[1].get_pos().get_z() <= 0 ) swap(varr[0], varr[1]);
                        else if(varr[2].get_pos().get_z() <= 0 ) swap(varr[0], varr[2]);
                }
                if( varr[2].get_pos().get_z() <= 0 ) swap(varr[1], varr[2]);

                if( varr[1].get_pos().get_z() <= 0){
                        Vertex v2_v0 = {intersect_line<float>(varr[2].get_pos(), varr[0].get_pos(), 1)};
                        Vertex v2_v1 = {intersect_line<float>(varr[2].get_pos(), varr[1].get_pos(), 1)};
                        Triangle t0(v2_v0, v2_v1, varr[2]);
                        wiremesh.erase(wiremesh.begin() + i);
                        new_triangles.push_back(t0);
                        i--;
                }
                else{
                        Vertex v0_v2 = {intersect_line<float>(varr[0].get_pos(), varr[2].get_pos(), 1)};
                        Vertex v0_v1 = {intersect_line<float>(varr[0].get_pos(), varr[1].get_pos(), 1)};
                        Triangle t0(v0_v2, varr[1], v0_v1);
                        Triangle t1(varr[1], varr[2], v0_v2);
                        wiremesh.erase(wiremesh.begin() + i);
                        new_triangles.push_back(t0);
                        new_triangles.push_back(t1);
                        i--;
                }
        }        
        wiremesh.insert(wiremesh.begin(), new_triangles.begin(), new_triangles.end());
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

void Renderer::draw_line(const Vertex& v0, const Vertex& v1){

        float x0 = v0.get_x();
        float x1 = v1.get_x();
        float y0 = v0.get_y();
        float y1 = v1.get_y();
        float dx = x1 - x0;
        float dy = y1 - y0;
        if(std::abs(dx) > std::abs(dy)){
                if(x1 < x0){
                        swap(x1, x0);
                        swap(y1, y0);
                }
                float m = dy/dx;
                while(x0 < x1){
                        if(boundary(0, window_width - 1, window_width - std::round(x0)) && boundary(0, window_height - 1, window_height - std::round(y0))){
                                output_buffer.set_buffer(window_width - std::round(x0), window_height - std::round(y0), '#');
                        }
                        y0+=m;
                        x0++;
                }
        }
        else{
                if(y1 < y0){ 
                        swap(y1, y0);
                        swap(x1, x0);
                }
                float m = dx/dy;
                while(y0 < y1){
                        if(boundary(0, window_width - 1, window_width - std::round(x0)) && boundary(0, window_height - 1, window_height - std::round(y0))){
                                output_buffer.set_buffer(window_width - std::round(x0), window_height - std::round(y0), '#');
                        }
                        x0+=m;
                        y0++;
                }
        }
}
void Renderer::draw_wireframe(){
        for(const Triangle& t : wiremesh){
               draw_line(t.get_v0(), t.get_v1());
               draw_line(t.get_v1(), t.get_v2());
               draw_line(t.get_v2(), t.get_v0());
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
        cull();
        project();
        draw_wireframe();
        draw();
}
}//namespace