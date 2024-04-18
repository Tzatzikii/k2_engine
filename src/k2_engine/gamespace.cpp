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

}//namespace