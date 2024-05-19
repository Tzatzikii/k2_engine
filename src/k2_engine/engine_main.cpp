#include "engine_main.hpp"

namespace k2_engine{

void debug_fn();
//#define VALGRIND
void start_main(){  
#if defined VALGRIND
        debug_fn();
#else
        open_main_menu();

#endif
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
        GameSpace scene = scene_creator();
        InputHandler inputs = scene_binds(scene);
        GameSpace copy;
        scene.save("balls");
        copy.load("balls");
        std::ifstream asd("doesntexist");
        Renderer renderer(copy, 80, 60);
        renderer.render();
}
/**
 * TODO outputbuffert ostream-má alakítani (valahogy xd)
 */
void main_loop(GameSpace scene){

        init_console();
        InputHandler inputs = scene_binds(scene);
        Renderer renderer(scene, 80, 60);

        auto prev = std::chrono::high_resolution_clock::now(); 
        while(inputs.get_previous() != 'q'){
                float delta = get_delta(prev);
                prev = std::chrono::high_resolution_clock::now();
                inputs.handle_input();
                scene.gravitate();
                scene.tick(delta);
                renderer.render();
                //std::cout<<delta<<std::endl;
        }
        restore_console();
}

}