#include "gamespace.hpp"

namespace k2_engine{

void GameSpace::push_game_object(WorldElement* obj){
        if(!!dynamic_cast<Camera*>(obj))
                camera = dynamic_cast<Camera*>(obj);
        
        else if(!!dynamic_cast<LightSource*>(obj))
                lightsources.push_back(dynamic_cast<LightSource*>(obj));

        else if(!!dynamic_cast<DynamicObject*>(obj)){
                objects.push_back(dynamic_cast<Object*>(obj));
                dynamic_objects.push_back(dynamic_cast<DynamicObject*>(obj));
        }
        else{   
                objects.push_back(dynamic_cast<Object*>(obj));
                static_objects.push_back(dynamic_cast<StaticObject*>(obj));
        }
}

void GameSpace::gravitate(){
        if(camera->get_pos().get_y() > groundy + camera_height){
                camera->translate(0, -0.1, 0);
                camera->set_motion(true);
        }
        else{
                camera->set_motion(false);
        }
}
}//namespace