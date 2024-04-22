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
        Renderer renderer(scene, 60, 30);
        Camera& cam = *new Camera(0,0,0,10,0,0,0);
        scene.push_game_object(&cam);
        scene.push_game_object(new StaticObject(Shape::Quad(VF(20,0,0),VF(20,0,10),VF(20,10,10),VF(20,10,0))));
        char c = 0;
        char d = 0;
        while(c != 'q'){
                if(d = outp::kbhit()) c = std::getchar();
                else c = 0;
                if(c == 'l') cam.rotate(0,0.1,0);
                if(c == 'h') cam.rotate(0,-0.1,0);
                if(c == 'w') cam.translate(0,0,0.4);
                if(c == 's') cam.translate(0,0,-0.4);
                renderer.render();
        }
}
}