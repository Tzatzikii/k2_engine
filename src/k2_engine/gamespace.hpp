#ifndef K2_ENGINE_GAMESPACE_HPP_
#define K2_ENGINE_GAMESPACE_HPP_

#include "world_elements.hpp"
#include <memory>

namespace k2_engine{

class GameSpace{
        float gravity;
        Camera* camera;
        std::vector<WorldElement*> world_elements;
        std::vector<LightSource*> lightsources;
        std::vector<Object*> objects;
        std::vector<DynamicObject*> dynamic_objects;
        std::vector<StaticObject*> static_objects;
public:
        explicit GameSpace(float gravity): gravity(gravity){}
        void push_game_object(WorldElement* obj);
        void init_gamespace();
        
        const Camera& get_camera() const { return *camera; }
        std::vector<WorldElement*> get_world_elements() const { return world_elements; }
        std::vector<Object*> get_objects() const { return objects; }
        ~GameSpace(){
                for( WorldElement* obj : world_elements ) delete obj;
        }

};

}//namespace
#endif //K2_ENGINE_GAMESPACE_HPP_