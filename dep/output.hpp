/**
 * @file output.hpp
 * @author Klemm Gábor  - Neptun: H8XK58
 * @brief A terminálba (stdout-ra) íráshoz egy eszköz, amit több külső forrásból,
 *        és saját tudásból építettem fel. Az eredeti forrásokat az adott helyen
 *        linkeltem a dokumentációban.
 *        
 *        Itt van megvalósítva a kurzor elrejtése valamint az user input közvetlen
 *        elérése a kellemesebb felhasználói  élmény  reményében,  ie.: ne kelljen
 *        minden input után ENTER-t lenyomni, hogy regisztrálódjon, vagy ne álljon
 *        le a program futása, mert éppen egy inputot várunk hogy mozgoghassunk
 * @version 0.1
 * @date 2024-03-08
 * 
 * 
 * 
 */

#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "utils.hpp"
#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

/**
 * TODO konstansokba át kell őket írni
 * 
 */
#define ARROW_LEFT 37
#define ARROW_UP 38
#define ARROW_RIGHT 39
#define ARROW_DOWN 40

namespace outp{

/**
 * @brief Az alábbi "nyers" kiírás mód platform specifikus,
 *        ezért külön definiálom a linuxos és windowsos
 *        függényeket
 *        Ezeket nem saját módszerrel írtam, a forrás a megfelelő
 *        függvény leírásánál található
 */
#ifdef __linux__
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

/**
 * @brief Csak az organizálás miatt szedtem egy strukrútába
 *        a két állapotot
 *        A nyers mód alapverően annyit csinál, hogy közvetlenül
 *        el lehet érni a felhasználói inputot az operációs renszer
 *        "közbeszólása" nélkül
 * @param original - Az output.cpp forráskódban egy konstans,
 *                   ami egy olyan struktúra ami eltárolja
 *                   az adott terminált és annak tulajdonságait,
 *                   majd ennek a segítségével lehet manipulálni azt
 * @note  További infó az alábbi linken:
 *        https://www.gnu.org/software/mit-scheme/documentation/stable/mit-scheme-ref/Terminal-Mode.html
 */
struct Rawmode{
        /**
         * @brief Bekapcsolja a nyers módot, ezt kicsit hosszabban leírom:

         *        Először a terminál struktúra állapotát lehívja és eltárolja 
         *        a fent említett osztályba, hogy azt később le lehessen kérni
         *        és az atexit() függvénnyel ismét alapállapotba helyezni
         *        az aktuális folyamat lefutása után
         *
         *        Ezután létrehoz egy új osztályt, amit manipulálni szeretnénk,
         *        ennek kikapcsolja az ECHO és az ICANON módot, hogy ne jelenjen meg
         *        a karakter amit leütünk (ECHO), valamint, hogy sor helyett
         *        byte-onként lehessen beolvasni a leütött karaktert
         *
         *        Ezek az említett flagek ún. bit flagek, ezért bit szerinti operátorral kell őket
         *        manipulálni
         *
         *        Végül ezeket a változtatásokat applikálni kell, itt a TCSAFLUSH megadja, hogy
         *        mikor szeretnénk a változtatást látni
         *        
         * @note  További információ és kód az alábbi linken:
         *        https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
         */
        static void enable();
        /**
         * @brief A fent említett konstans osztályba elmentett tulajdonságokat olvassa
         *        ki a futás végén, hogy alapállapotba állítsa a terminált
         * 
         */
        static void disable();

};

/**
 * @brief Megadja, hogy hány byte input várakozik az output bufferben
 * !Az említett output buffer nem az általam deklarált OutputBuffer class
 * @return int - a byte-ok száma
 * @note Link a forráshoz:
 *       https://github.com/ShakaUVM/colors/blob/master/colors.h
 */
int kbhit();

#endif //__linux__

/**
 * @brief A temrinál kurzort jellemző osztály,
 *        ami azt manipuláló metódusokat tartalmaz,
 *        és ANSI escape sequenceket használ
 * @note https://en.wikipedia.org/wiki/ANSI_escape_code
 */
struct Cursor{
        /**
         * @brief Elrejti a kurzort a
         *        "\x1B[?25l" sorozattal
         */
        static void hide();
        /**
         * @brief Megjeleníti a kurzort a 
         *        "\x1B[?25h" sorozattal
         */
        static void show();
        /**
         * @brief Adott sorba és oszlopba mozgatja
         *        a terminál kurzort
         * @param x - Az oszlop száma
         * @param y - A sor száma
         */
        static void move(size_t x, size_t y);
        /**
         * @brief Alaphelyzetbe állítja a terimál kurzort,
         *        azaz a (0,0) koordinátákba mozgatja, a bal felső sarokba,
         *        és megjeleníti a show() szekvenciával
         */
        static void reset();
        /**
         * @brief Leíró név ismét, a terminálba írt szöveg színét változtatja
         *        RGB(A?) értékek alapján
         */
        static void set_color(unsigned char R, unsigned char G, unsigned char B);
        static void set_background_color(unsigned char R, unsigned char G, unsigned char B);

};
void rgba_pixel(unsigned char R, unsigned char B, unsigned char G, unsigned char A, unsigned x, unsigned y );
inline void clrscrn(){ std::cout << "\x1B[2J"; }


/**
 * @brief 
 * A terminálban képes adott koordinátákra kiírni egy adott karaktert
 * @tparam T - Karakter vagy int, hiszen máshogy írodnak ki stdout-ra
 * @param x - Hányadik oszlopba írunk
 * @param y - Hányadik sorba írunk, lefelé növekszik
 * @param c - Kiírandó karakter
 * @param duplicate - A karakterek aránytalan dimenzióját
 *                    lehet korrigáni duplikálással,
 *                    alapból igaz az értéke
 * @param stretch - Kétszeresre szorozza az oszlopszámot, hogy
 *                  a duplikálásnak adjon értelmet
 */
template <typename T>
inline void cout_xy(size_t x, size_t y, const T c, bool duplicate = true, bool stretch = true){

        if(stretch) x*=2;
        Cursor().move(x, y);
        std::cout << c;
        if(duplicate) std::cout << c;

}

struct colored_char{
        char c;
        unsigned char r, g, b;

        colored_char(const colored_char& cc) : c(cc.c), r(cc.r), g(cc.g), b(cc.b){}
        colored_char(const char c) : c(c), r(208), g(207), b(204){}
        friend std::ostream& operator<<(std::ostream& os, colored_char cc){
                Cursor::set_color(cc.r, cc.g, cc.b);
                os << cc.c;
                return os;
        }
};

/**
 * @brief Kiírás előtt bele lehet írni a megjelenítendő karaktereket,
 *        hogy sokkal simább legyen a megjelenítés
*/
class OutputBuffer{

        size_t bufferwidth; //< A buffer szélessége
        size_t bufferheight; //< A buffer magassága
        std::vector<std::vector<colored_char>> buffer; //< Maga a kétdimenziós buffer tömb

public:
        /**
         * @brief Létrehozza magát a buffert
         *        Nincs default értéke, hiszen minden buffer méretét illik tudni
         * 
         * @param bufferwidth - Ld. feljebb
         * @param bufferheight - Ld. feljebb
         */
        OutputBuffer(size_t bufferwidth, size_t bufferheight);

        /**
         * @brief Kiüríti a buffert
         * 
         */
        void clear_buffer();

        /**
         * @brief Adott indexre lehet tölteni a bufferbe, túlindexelés
         *        elkerülésére assert-álja az indexeket
         * 
         * @param i - Az oszlop indexe
         * @param j - A sor indexe
         * @param c - A bufferbe irandó karakter
         */
        void set_buffer(size_t i, size_t j, colored_char c);

        /**
         * @brief Kiírja a buffer tartalmát a standart output-ra
         * a megfelelő oszlop- és sorindexű helyre
         */
        void push_to_stdout();

};

} //namespace outp

#endif //OUTPUT_HPP_