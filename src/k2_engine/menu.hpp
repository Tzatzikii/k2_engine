#ifndef K2_ENGINE_MENU_HPP_
#define K2_ENGINE_MENU_HPP_

#include <iostream>
#include <sstream>
#include "gamespace.hpp"

namespace k2_engine{

void main_loop(GameSpace);

void open_main_menu();
void open_ingame_menu(k2_engine::GameSpace*);

}//namespace
k2_engine::GameSpace scene_creator();
k2_engine::GameSpace load_scene(std::string fname);

#endif