#include "output.hpp"

namespace outp{

const char* ALPHASCALE = " .`:,;'_^\"></-!~=)(|j?}{][ti+l7v1%yrfcJ32uIC$zwo96sngaT5qpkYVOL40&mG8*xhedbZUSAQPFDXWK#RNEHBM@";

#ifdef __linux__



static struct termios original;
void Rawmode::disable(){
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void Rawmode::enable(){

        tcgetattr(STDIN_FILENO, &original);
        struct termios raw = original;
        atexit(disable);
        raw.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}

int kbhit(){

        int count = 0;
        ioctl(STDIN_FILENO, FIONREAD, &count);
        return count;

}

#endif //__linux__

void Cursor::hide(){ std::cout << "\x1B[?25l"; atexit(show);}
void Cursor::show(){ std::cout << "\x1B[?25h";}
void Cursor::move(size_t x, size_t y){ std::cout << "\x1B[" << y << ';' << x << 'H'; }
void Cursor::reset(){move(0, 0); show();}
void Cursor::set_color(unsigned char R, unsigned char G, unsigned char B){
        std::cout << "\x1B[38;2;" << (int)R << ';' << (int)G << ';' << (int)B << 'm';
}
void Cursor::set_background_color(unsigned char R, unsigned char G, unsigned char B){
        std::cout << "\x1B[48;2;" << (int)R << ';' << (int)G << ';' << (int)B << 'm';
}



void rgba_pixel(unsigned char R, unsigned char B, unsigned char G, unsigned char A, unsigned x, unsigned y ){
        size_t alphascale_size = std::strlen(ALPHASCALE);
        float alpha_ratio = alphascale_size/255;
        char alpha_char = ALPHASCALE[(int)round(A*alpha_ratio)];
        Cursor().set_color(0, 0, 0);
        Cursor().set_background_color(R, G, B);
        cout_xy<char>(x, y, alpha_char);
        
}
OutputBuffer::OutputBuffer(size_t bufferwidth, size_t bufferheight):bufferwidth(bufferwidth),bufferheight(bufferheight){

        for(int i = 0; i < bufferwidth; i++){

                std::vector<colored_char> column;
                buffer.push_back(column);
                for(int j = 0; j < bufferheight; j++){
                buffer[i].push_back(' ');

                }
        }
}
void OutputBuffer::set_buffer(size_t i, size_t j, colored_char c){
        assert(i >= 0 && i < bufferwidth);
        assert(j >= 0 && j < bufferheight);
        buffer[i][j] = c;
}

void OutputBuffer::push_to_stdout(){

        for(int i = 0; i < bufferwidth; i++){

                for(int j = 0; j < bufferheight; j++){
                        cout_xy<colored_char>(i, j, buffer[i][j]);
                }
        }
}
void OutputBuffer::clear_buffer(){

        for(int i = 0; i < bufferwidth; i++){

                for(int j = 0; j < bufferheight; j++){
                        buffer[i][j] = ' ';
                }
        }
}

} //namespace outp