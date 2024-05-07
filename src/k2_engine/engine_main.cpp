#include "engine_main.hpp"

namespace k2_engine{

void debug_fn();

void start_main(){  
        init_console();
       // debug_fn();
        main_loop();

        restore_console();
}

void init_console(){
        outp::Rawmode::enable();
        outp::Cursor::hide();
}

void restore_console(){
        outp::clrscrn();
        outp::Cursor::move(0,0);
        outp::Rawmode::disable();
        outp::Cursor::show();
}
using k2_math::Vec4;
#define VF(x,y,z) Vec4<float>(x,y,z)
void debug_fn(){
        GameSpace scene(0);
        Renderer renderer(scene, 60, 30);
        Camera* cam = new Camera(0,0,0,10,0,0,3.14/2);
        scene.push_game_object(cam);
        scene.push_game_object(new StaticObject(Shape::Quad(VF(20,0,0),VF(20,0,10),VF(20,10,10),VF(20,10,0))));
        renderer.render();
}

void main_loop(){
        GameSpace scene(0);
        Renderer renderer(scene, 90, 40);
        Camera& cam = *new Camera(0,5,0,20,0,0,0);
        scene.push_game_object(&cam);
        scene.push_game_object(new StaticObject(Shape::Quad(VF(10,20,20),VF(10,0,20),VF(0,0,20),VF(0,20,20))));
        InputHandler inputs(scene);
        inputs.bind('w', move_forward);
        inputs.bind('s', move_backward);
        inputs.bind('a', move_left);
        inputs.bind('d', move_right);
        inputs.bind('l', rotate_right);
        inputs.bind('j', rotate_left);
        inputs.bind('k', look_up);
        inputs.bind('i', look_down);
        while(inputs.get_previous() != 'q'){
                inputs.handle_input();
                renderer.render();
        }
}
}