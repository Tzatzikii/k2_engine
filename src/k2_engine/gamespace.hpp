/**
 * @file gamespace.hpp
 * @author Klemm Gábor (H9XK58)
 * @brief Maga a játéktér tulajdonképpen, ő tartalmaz minden megjelenített objektumot / folyamatot
 * @version 0.1
 * @date 2024-05-17
 * 
 * 
 */
#ifndef K2_ENGINE_GAMESPACE_HPP_
#define K2_ENGINE_GAMESPACE_HPP_

#include "world_elements.hpp"
#include <fstream>
#include <memory>
#include <algorithm>

namespace k2_engine{

/**
 * @brief A játéktérben lévő elemek tárolására szolgál
 * 
 */
class GameSpace{
        float gravity; // < gravitáció, mint a valóságban
        float groundy; // < talaj y koordinátája
        float camera_height; // < kamera magassága, kb mint egy ember szemei, hogy ne a talajon legyen közvetlen
        Camera* camera; // < 
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
                delete camera;
        }
        float get_groundy() const { return groundy; } 
        void gravitate();
        void tick(float delta);

        void save(const char* fname);
        void read(const char* fname);

        friend std::ofstream& operator<<(std::ofstream& os, const GameSpace& gs);
        friend std::ifstream& operator>>(std::ifstream& is, GameSpace& gs);

};

}//namespace
#endif //K2_ENGINE_GAMESPACE_HPP_