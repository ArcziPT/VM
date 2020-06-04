#include "VMScreen.h"

#include "Debug.h"

VMScreen::VMScreen(int width, int height) : width(width), height(height){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return; //error


    window = SDL_CreateWindow("VM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    if(window == NULL)
        return; //error

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        return; //error

    screen_surface = SDL_GetWindowSurface(window);


    //start main loop thread
    main_thread = std::thread([this]()->void{main_loop();});
}

VMScreen::~VMScreen(){
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);

    quit = true;
    main_thread.join();

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void VMScreen::main_loop(){
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT)
                quit = true;
        }
    }

    //TODO: mouse an keyboard
}

void VMScreen::set_color(int r, int g, int b){
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void VMScreen::draw_line(int sx, int sy, int fx, int fy){
    SDL_RenderDrawLine(renderer, sx, sy, fx, fy);
    SDL_RenderPresent(renderer);
}

void VMScreen::clear(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}