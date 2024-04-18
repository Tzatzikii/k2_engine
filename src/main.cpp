#include "k2_engine/engine_main.hpp"

//#define CPORTA

#ifdef CPORTA
#include "../test/logics_module_test.hpp"
#endif

using k2_engine::start_main;

int main(){

        #ifdef CPORTA 
        start_gtest();
        #endif

        #ifndef CPORTA 
        start_main();
        #endif  
        
        return 0;
}