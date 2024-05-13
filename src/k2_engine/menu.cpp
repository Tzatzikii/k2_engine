#include "menu.hpp"

namespace k2_engine{

extern void main_loop();

void open_main_menu(){
        std::cout<<"[Main menu] \n" 
        << "\t1: New game       \n"
        << "\t2: Load game      \n"
        << "\t3: Help           \n"
        << "\t4: Credits        \n"
        <<                     '\n'
        << "[Choice]";
        ushort choice;
        bool exit_cond = false;
        while(!exit_cond){
                std::cin>>choice;
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
                }
        }
}
}//namespace