#ifndef VM_SCREEN_H
#define VM_SCREEN_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <thread>

//TODO: implement Screen

//!
//! \class VMScreen managing screen with SDL2
//! 
class VMScreen{
public:
    //! creates VMScreen with specified resolution
    VMScreen(int width = 800, int height = 600);
    ~VMScreen();

    void set_color(int r, int g, int b);

    //! @param sx x coordinate of starting point
    //! @param sy y coordinate of starting point
    //! @param fx x coordinate of ending point
    //! @param fy y coordinate of ending point
    void draw_line(int sx, int sy, int fx, int fy);

    //! @param text pointer at '\0'-ending string
    void put_text(char* text, int x, int y);

    //! @param path path to font file
    //! @param sz size of font
    void set_font(const std::string& path, int sz);
    void clear();

private:
    int width;
    int height;

    int r=255,g=255,b=255;
    TTF_Font* font = NULL;

    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;
    SDL_Renderer* renderer = NULL;

    bool quit = false; //!< exit flag
    std::thread main_thread; //!< thread for screen managing(SDL thread)
    void main_loop();
};

#endif