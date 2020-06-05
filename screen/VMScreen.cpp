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

    if(TTF_Init() != 0)
        return; //error

    //start main loop thread
    main_thread = std::thread([this]()->void{main_loop();});
}

VMScreen::~VMScreen(){
    //DEBUG
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);

    quit = true;
    main_thread.join();

    TTF_Quit();

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

    //TODO: mouse and keyboard
}

void VMScreen::set_color(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void VMScreen::draw_line(int sx, int sy, int fx, int fy){
    SDL_RenderDrawLine(renderer, sx, sy, fx, fy);
    SDL_RenderPresent(renderer);
}

void VMScreen::put_text(char* text, int x, int y){
    SDL_Color color = {r, g, b};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    TTF_SizeText(font, text, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, Message, NULL, &rect);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);
}

void VMScreen::set_font(const std::string& path, int sz){
    if(font != NULL)
        TTF_CloseFont(font);
    font = TTF_OpenFont(path.c_str(), sz);
    LOG_OBJECT(font)
}

void VMScreen::clear(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}