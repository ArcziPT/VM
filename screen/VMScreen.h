#ifndef VM_SCREEN_H
#define VM_SCREEN_H

#include <vector>
#include <SDL2/SDL.h>
#include <thread>

//TODO: implement Screen

class VMScreen{
public:
    VMScreen(int width = 800, int height = 600);
    ~VMScreen();

    void set_color(int r, int g, int b);
    void draw_line(int sx, int sy, int fx, int fy);
    void clear();

private:
    int width;
    int height;

    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;
    SDL_Renderer* renderer = NULL;

    bool quit = false;
    std::thread main_thread;
    void main_loop();
};

#endif