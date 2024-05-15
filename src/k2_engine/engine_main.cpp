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
        auto prev = std::chrono::high_resolution_clock::now();
        int i = 0;
        while(i < 10){
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> dur = now-prev;
                std::chrono::seconds s;
                float delta = dur.count()/s.count();
                prev = now;
                std::cout << std::setprecision(9) << std::showpoint  << std::fixed << delta << std::endl;
                i++;
        }
}
/**
 * TODO outputbuffert ostream-má alakítani (valahogy xd)
 */
void main_loop(){

        GameSpace scene = scene_creator();
        InputHandler inputs = scene_binds(scene);
        Renderer renderer(scene, 80, 60);
        std::cout << "\x1b[3m";

        auto prev = std::chrono::high_resolution_clock::now(); 
        while(inputs.get_previous() != 'q'){
                float delta = get_delta(prev);
                inputs.handle_input();
                scene.gravitate();
                scene.tick();
                renderer.render();
        }
}

}