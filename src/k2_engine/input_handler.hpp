/**
 * @file input_handler.hpp
 * @author Klemm Gábor (H8XK58)
 * @brief User inputok kezelésének konnyítésére létrehozott modul
 * @version 0.1
 * @date 2024-05-18
 * 
 * 
 */
#ifndef K2_ENGINE_INPUT_HANDLER_HPP_
#define K2_ENGINE_INPUT_HANDLER_HPP_

#include "menu.hpp"
#include "../../dep/output.hpp"
#include "world_elements.hpp"
#include "gamespace.hpp"
#include "menu.hpp"
#include <unordered_map>


namespace k2_engine{

/**
 * @brief Előre definiált funkciókat tartalmaz, key bindingnél van értelme
 * 
 */
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

/**
 * @brief Inputok kezelését végző osztály
 * 
 */
class InputHandler{
        GameSpace* scene; // < a játéktér aminek kezeldi szeretnénk az eseményeit
        std::unordered_map<char, control> binds; // < minél gyorsabb elérés miatt egy hash táblában tárolja a bindokat

        char current; // < az aktuálisan leütött billentyű
        char previous; // < az előőző billenytű
        size_t queue; // < a bufferben várakozó inputok száma
public:
        InputHandler(GameSpace& scene):scene(&scene), current(0), previous(0), queue(0){}
        char get_current() const { return current; }
        char get_previous() const { return previous; }
        size_t get_queue_size() const { return queue; }
        /**
         * @brief hozzárendel egy billentyűt egy kontrolfunkcióhoz
         * 
         * @param key tetszőleges karakter
         * @param action egy előre megadott funkció
         */
        void bind(char key, control action);
        void unbind(char key);
        void handle_input();
};
} // namespace

#endif