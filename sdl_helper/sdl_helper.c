#include "sdl_helper.h"
#include <SDL_image.h>

struct SDL_Window* createWindow()
{
    printf("Creating window\n");
    struct SDL_Window* window = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("failed to initialize sdl: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Move Sprite Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,900, 900, SDL_WINDOW_SHOWN);
    if( window == NULL )
    {
        printf("Window not created: %s\n", SDL_GetError());
        exit(2);
    }

    return window;
}

struct SDL_Surface* getSurface(struct SDL_Window* window)
{
    struct SDL_Surface* mainSurface = NULL;
    mainSurface = SDL_GetWindowSurface(window);
    if( mainSurface == NULL )
    {
        printf("Could not get surface of window: %s\n", SDL_GetError());
        exit(3);
    }
}

struct SDL_Renderer* createRenderer(struct SDL_Window* window)
{
    struct SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if( renderer == NULL )
    {
        printf("Could not creater renderer: %s\n", SDL_GetError());
        exit(3);
    }
    SDL_SetRenderDrawColor(renderer,  0xFF, 0xFF, 0xFF, 0xFF);
    return renderer;
}

void setLoadType(int imgLoadType)
{
    if( !( IMG_Init( imgLoadType ) & imgLoadType ) )
    {
        printf("Img type could not be set: %s\n", SDL_GetError());
        exit(4);
    }
}

struct SDL_Texture* loadTexture(SDL_Renderer* renderer, char* fpath)
{
    SDL_Texture* texture = NULL;
    SDL_Surface *imageSurface  = NULL;

    imageSurface = IMG_Load(fpath);
    if( imageSurface == NULL )
    {
        printf("Could not load image %s %s\n", fpath, SDL_GetError());
        exit(5);
    }

    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if( texture == NULL )
    {
        printf("Could not load texture: %s\n", SDL_GetError());
        exit(6);
    }
    SDL_FreeSurface(imageSurface);

    return texture;
}



void renderImage(SDL_Renderer *renderer, char *image)
{
    SDL_Texture *texture  = loadTexture(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
}

void drawRect(SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect fillRect = {x,y,100,100};
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 0xFF );  
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderPresent(renderer);
}

void draw_sprite(SDL_Renderer *renderer, SDL_Texture *sprite_texture, int x, int y)
{
    SDL_Rect pos_rect = {x,y,100,100};
    SDL_RenderCopy(renderer, sprite_texture,NULL, &pos_rect );
    SDL_RenderPresent(renderer);
}

void reset_screen(SDL_Renderer* renderer)
{
    SDL_Rect fillRect = {0,0,900,900};
    SDL_SetRenderDrawColor( renderer, 225, 225, 225, 0 );  
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderPresent(renderer);
}

SDL_Texture* load_sprite_texture(char* image, SDL_Renderer *renderer)
{
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *sprite_surface = IMG_Load(image);
    SDL_Texture *sprite_texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);

    return sprite_texture;
}
