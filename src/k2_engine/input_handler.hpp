#ifndef K2_ENGINE_INPUT_HANDLER_HPP_
#define K2_ENGINE_INPUT_HANDLER_HPP_

#include "../../dep/output.hpp"
#include "world_elements.hpp"
#include "gamespace.hpp"
#include <unordered_map>


namespace k2_engine{

enum control{
        move_forward,
        move_backward,
        move_left,
        move_right,
        ascend,
        descend,
        jump,
        crouch,
        rotate_left,
        rotate_right,
        look_up,
        look_down
};

class InputHandler{
        GameSpace* scene;
        std::unordered_map<char, control> binds;

        char current;
        char previous;
        size_t queue;
public:
        InputHandler(GameSpace& scene):scene(&scene), current(0), previous(0), queue(0){}
        char get_current() const { return current; }
        char get_previous() const { return previous; }
        size_t get_queue_size() const { return queue; }
        void bind(char key, control action);
        void handle_input();
};
} // namespace

#endif