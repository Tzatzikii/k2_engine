#include "menu.hpp"

namespace k2_engine{

extern void main_loop();

void open_main_menu(){
        std::cout<<"[Main menu] \n" 
        << "\t1: New game       \n"
        << "\t2: Load game      \n"
        << "\t3: Help           \n"
        << "\t4: Credits        \n"
        << "\t5: Exit           \n"
        <<                     '\n'
        << "[Choice]";
        ushort choice;
        bool exit_cond = false;
        while(!exit_cond){
                std::cin>>choice;
                std::cout << choice;
                switch(choice){
                        default:{
                                std::cout << "Please choose from the options above";
                                break;
                        }
                        case 1:{
                                main_loop(); 
                                exit_cond = true;
                                break;
                        }
                        case 5:{
                                exit_cond = true;
                                break;
                        }
                }
        }
}

void open_ingame_menu(){

}
}//namespace