#include "gamespace.hpp"

namespace k2_engine{

GameSpace::GameSpace(float gravity, float camera_height, float goundy): gravity(gravity), camera_height(camera_height), groundy(groundy){
        camera = new Camera(0, groundy + camera_height, 0);
        this->groundy = 0; 
}

void GameSpace::add(WorldElement* obj){
        if(dynamic_cast<LightSource*>(obj) != nullptr)
                lightsources.push_back(dynamic_cast<LightSource*>(obj));

        else if(dynamic_cast<DynamicObject*>(obj) != nullptr){
                objects.push_back(dynamic_cast<Object*>(obj));
                dynamic_objects.push_back(dynamic_cast<DynamicObject*>(obj));
        }
        else{   
                objects.push_back(dynamic_cast<Object*>(obj));
                static_objects.push_back(dynamic_cast<StaticObject*>(obj));
        }
}

void GameSpace::gravitate(){
        if(camera->get_pos().get_y() > groundy + camera_height) camera->translate(k2_math::Vec4<float>(0, -0.1, 0));
        //camera->move(0.0, -0.1, 0.0);
}

void GameSpace::tick(){
        if(camera)
        camera->tick(groundy);
}
}//namespace