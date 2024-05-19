#include "menu.hpp"
namespace k2_engine{



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
                                main_loop(scene_creator()); 
                                exit_cond = true;
                                break;
                        }
                        case 2:{
                                GameSpace gs;
                                std::string fname;
                                std::cout << "Type in a save name";
                                std::cin >> fname;
                                main_loop(load_scene(fname));
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

void open_ingame_menu(GameSpace* scene){
        std::cout<<"[Paused]    \n"
        <<"\t1: Save    ,       \n"
        <<"\t2: Back            \n"
        << "[Choice]";
        
        outp::Rawmode::disable();
        outp::Cursor::show();

        ushort choice;
        std::cin >> choice;
        switch(choice){
                case 1:{
                        std::string fname;
                        std::cin>>fname;
                        scene->save(fname);
                        break;
                }
                default: break;
        }
        outp::Rawmode::enable();
        outp::Cursor::hide();

}
}//namespace