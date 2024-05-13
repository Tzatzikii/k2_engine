#include "engine_main.hpp"

namespace k2_engine{

void debug_fn();

void start_main(){  
        init_console();
        //debug_fn();
        open_main_menu();

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
void debug_fn(){
}
void main_loop(){

        GameSpace scene = scene_creator();
        InputHandler inputs = scene_binds(scene);
        Renderer renderer(scene, 80, 60);
        while(inputs.get_previous() != 'q'){
                inputs.handle_input();
                scene.gravitate();
                scene.tick();
                renderer.render();
        }
}
}