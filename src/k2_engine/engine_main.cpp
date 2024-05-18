#include "engine_main.hpp"

namespace k2_engine{

void debug_fn();
#define VALGRIND
void start_main(){  
#if defined VALGRIND
        debug_fn();
#else
        init_console();
        open_main_menu();

        restore_console();
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
        std::ofstream os("TESTSAVE.txt");
        os << scene;
        GameSpace copy;
        std::ifstream is("TESTSAVE.txt");
        is >> copy;
        Renderer renderer(copy, 80, 60);
        //renderer.render();
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
                prev = std::chrono::high_resolution_clock::now();
                inputs.handle_input();
                scene.gravitate();
                scene.tick(delta);
                renderer.render();
                //std::cout<<delta<<std::endl;
        }
}

}