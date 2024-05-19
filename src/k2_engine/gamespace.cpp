#include "gamespace.hpp"

namespace k2_engine{


GameSpace::GameSpace(float gravity, float camera_height, float goundy): gravity(gravity), camera_height(camera_height), groundy(groundy){
        camera = new Camera(0, groundy + camera_height, 0);
        this->groundy = 0; 
}

void GameSpace::add(WorldElement* obj){
// ??????????????????????????????????????????????????????? goofy ahh !oop implementáció
        world_elements.push_back(obj);
        if(dynamic_cast<LightSource*>(obj) != nullptr){
                lightsources.push_back(dynamic_cast<LightSource*>(obj));
        }
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

void GameSpace::tick(float delta){
        if(camera)
        camera->tick(groundy);
        for(DynamicObject*& obj : dynamic_objects) obj->tick(delta);
}

std::ofstream& operator<<(std::ofstream& os, const GameSpace& gs){
        os<<gs.gravity<<';'<<gs.groundy<<';'<<gs.camera_height<<std::endl;
        gs.camera->write(os);
        for(const WorldElement* const we : gs.world_elements){
               we->write(os);
        }
        return os;
}
std::ifstream& operator>>(std::ifstream& is, GameSpace& gs){
        ((is>>gs.gravity).ignore(1, ';')>>gs.groundy).ignore(1, ';')>>gs.camera_height;
        gs.camera->read(is);
        char objid;
        while(!is.eof()){
                (is.ignore(2, '.') >> objid).ignore(1, ';');
                switch(objid){
                        case 'S':{
                                StaticObject* obj = new StaticObject;
                                obj->read(is);
                                gs.add(obj);
                                break;
                        }
                        case 'T':{
                                TestDynamicObject* obj = new TestDynamicObject;
                                obj->read(is);
                                gs.add(obj);
                                break;
                        }
                }
        }
        return is;
}
void GameSpace::save(const std::string& fname) const{
        std::ofstream os(fname + ".ktwo");
        os << *this;
}
void GameSpace::load(const std::string& fname){
        std::ifstream is(fname + ".ktwo");
        is >> *this;
}

}//namespace