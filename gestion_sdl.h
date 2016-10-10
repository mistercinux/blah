#ifndef GESTION_SDL_H
#define GESTION_SDL_H
#include <exception>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class sdl_exception: std::exception
{
    protected:
    std::string msg__;

    public:
    sdl_exception(const std::string& msg)
    {
        msg__ = msg + ": ";
        msg__ += SDL_GetError();
    }
    sdl_exception(const std::string msg, const std::string& errmsg)
    {
        msg__ = msg + ": " + errmsg;
    }

    ~sdl_exception () throw() { }
    const char* what() const throw() { return msg__.c_str(); }
};

class gestion_sdl
{
    int SCREEN_W;
    int SCREEN_H;

    std::string windowTitle;

    public:
    SDL_Window*     mainWindow__      = nullptr;
    SDL_Renderer*   mainRenderer__    = nullptr;
    SDL_Texture*    backgroundTex__   = nullptr;
    SDL_Texture*    playerTex__       = nullptr;
    SDL_Texture*    greenRocketTex__  = nullptr;
    SDL_Texture*    hostileTex__      = nullptr;

    SDL_Texture *loadTexture(const std::string& path);

    int getWidth()  { return SCREEN_W; }
    int getHeight() { return SCREEN_H; }
    void init(const std::string& bgPath, const std::string& playerPath, const std::string& hostilePath, const std::string& greenRocketPath);
    void createRenderer();
    void renderClear () { SDL_RenderClear(mainRenderer__); }
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);



    ~gestion_sdl ();
};




#endif
