#include "gestion_sdl.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

SDL_Texture* gestion_sdl::loadTexture(const std::string& path)
{
    SDL_Texture *texture = IMG_LoadTexture(mainRenderer__, path.c_str());
    printf("Chargement de l'image %s ...\n", path.c_str());

    if (texture == nullptr)
    {
        throw sdl_exception("loadTexture", IMG_GetError());
    }
    return texture;
}


void gestion_sdl::init(const std::string& bgPath, const std::string& playerPath, const std::string& greenRocketPath)
{
    SCREEN_W = 640;
    SCREEN_H = 480; 
    windowTitle  = "Hello World";

    if(SDL_Init(SDL_INIT_VIDEO)<0) { throw sdl_exception("SDL_Init"); }

    mainWindow__ = SDL_CreateWindow(windowTitle.c_str(), 100, 100, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (mainWindow__ == nullptr) { throw sdl_exception("SDL_CreateWindow"); }

    mainRenderer__ = SDL_CreateRenderer(mainWindow__, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mainRenderer__ == NULL){ throw sdl_exception("SDL_CreateRenderer"); }

    backgroundTex__  = loadTexture((&bgPath)->c_str());
    playerTex__      = loadTexture((&playerPath)->c_str());
    greenRocketTex__ = loadTexture((&greenRocketPath)->c_str());
}

void gestion_sdl::createRenderer() 
{
    mainRenderer__ = SDL_CreateRenderer(mainWindow__, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mainRenderer__ == nullptr)
    {
        throw sdl_exception("createRenderer");
    }
}


gestion_sdl::~gestion_sdl()
{
    if (greenRocketTex__) {
        SDL_DestroyTexture(greenRocketTex__);
    }
    if (playerTex__) {
        SDL_DestroyTexture(playerTex__);
    }
    if (backgroundTex__) {
        SDL_DestroyTexture(backgroundTex__);
    }
    if (mainRenderer__) {
        SDL_DestroyRenderer(mainRenderer__);
    }
    if (mainWindow__) {
        SDL_DestroyWindow(mainWindow__);
    }
    SDL_Quit();
    IMG_Quit();
}

