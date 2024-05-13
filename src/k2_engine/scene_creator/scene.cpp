#include "scene.hpp"
using namespace k2_engine;
using namespace k2_math;


GameSpace scene_creator(){
        GameSpace scene;
        scene.add(new StaticObject(Shape::Cube(VecF(0, 0, 15), VecF(0, 0, 0), 10.0f)));

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