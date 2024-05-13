#ifndef K2_ENGINE_GAMESPACE_HPP_
#define K2_ENGINE_GAMESPACE_HPP_

#include "world_elements.hpp"
#include <memory>

namespace k2_engine{

class GameSpace{
        float gravity;
        float groundy;
        float camera_height;
        Camera* camera;
        std::vector<WorldElement*> world_elements;
        std::vector<LightSource*> lightsources;
        std::vector<Object*> objects;
        std::vector<DynamicObject*> dynamic_objects;
        std::vector<StaticObject*> static_objects;

public:
        explicit GameSpace(float gravity = 10, float camera_height = 0, float goundy = 0);
        void add(WorldElement* obj);
        
        const Camera& get_camera() const { return *camera; }
        Camera* get_camera_ptr() { return camera; }
        std::vector<WorldElement*> get_world_elements() const { return world_elements; }
        std::vector<Object*> get_objects() const { return objects; }
        ~GameSpace(){
                for( WorldElement* obj : world_elements ) delete obj;
        }
        void gravitate();
        void tick();

};

}//namespace
#endif //K2_ENGINE_GAMESPACE_HPP_