#include "scene.hpp"
using namespace k2_engine;
using namespace k2_math;


GameSpace scene_creator(){
        GameSpace scene(10, 5, 0);
        scene.add(new StaticObject(Shape::Cube(VecF(0, 7.5, 10), VecF(0, 0, 0), 15.0f, VecRGB(255, 255, 0) )));

        return scene;
}

InputHandler scene_binds(GameSpace& scene){
        InputHandler inputs(scene);
        inputs.bind('w', move_forward);
        inputs.bind('s', move_backward);
        inputs.bind('a', move_left);
        inputs.bind('d', move_right);
        inputs.bind('j', rotate_left);
        inputs.bind('l', rotate_right);
        inputs.bind('k', look_up);
        inputs.bind('i', look_down);


        return inputs;
}