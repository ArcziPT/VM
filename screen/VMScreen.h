#ifndef VM_SCREEN_H
#define VM_SCREEN_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <thread>

//TODO: implement Screen

class VMScreen{
public:
    VMScreen(int width = 800, int height = 600);
    ~VMScreen();

    void set_color(int r, int g, int b);
    void draw_line(int sx, int sy, int fx, int fy);
    void put_text(char* text, int x, int y);
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

    bool quit = false;
    std::thread main_thread;
    void main_loop();
};

#endif