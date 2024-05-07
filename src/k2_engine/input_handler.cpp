#include "input_handler.hpp"
namespace k2_engine{

void InputHandler::bind(char key, control action){
        binds.insert(std::pair<char, control>(key, action));
}

void InputHandler::handle_input(){
        if(queue = outp::kbhit()) previous = current = std::getchar();
        bool binded = binds.find(current) != binds.end();
        if(!binded) return;
        control action = binds.find(current)->second;
        Camera* cam = scene->get_camera_ptr();

        bool m = cam->get_motion();
        switch(action){
                case move_forward:
                        if(!m) cam->translate(0.0, 0.0, 0.4);
                break;
                case move_backward:
                        if(!m) cam->translate(0.0, 0.0, -0.4);
                break;
                case move_left:
                        if(!m) cam->translate(0.4, 0.0, 0.0);
                break;
                case move_right:
                        if(!m) cam->translate(-0.4, 0.0, 0.0);
                break;
                case rotate_left:
                        cam->rotate(0.0, 0.1, 0.0);
                break;
                case rotate_right:
                        cam->rotate(0.0, -0.1, 0.0);
                break;
                case look_up:
                        cam->rotate(0.1, 0.0, 0.0);
                break;
                case look_down:
                        cam->rotate(-0.1, 0.0, 0.0);
                break;
                case jump:
                        if(!m) cam->translate(0.0, 4.0, 0.0);
                break;
                default:
                break;
        }
        current = 0;
}


}//namespace