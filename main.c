#include "position/position.h"
#include "sdl_helper/sdl_helper.h"

void main()
{
    struct position* pos = init_position(40, 400);
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;

    window = createWindow();
    renderer = createRenderer(window);
    renderImage(renderer, "track.bmp");

    SDL_Event event;
    int  hasquit = -1;
    
    drawRect(renderer, get_x(pos), get_y(pos));
    while(hasquit != 0)
    {
        while(hasquit != 0 && SDL_PollEvent(&event)!=0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    hasquit = 0;
                break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                     {
                        case SDL_SCANCODE_LEFT:
                            accelerate(pos, -30, 0);
                        break;
                        case SDL_SCANCODE_RIGHT:
                            accelerate(pos, 30, 0);
                        break;
                        case SDL_SCANCODE_UP:
                            accelerate(pos, 0, -30);
                        break;
                        case SDL_SCANCODE_DOWN:
                            accelerate(pos, 0, 30);
                        break;

                    }
                break;
            }
            
        }
        renderImage(renderer, "track.bmp");
        drawRect(renderer, get_x(pos), get_y(pos));
        SDL_Delay(100);
    }

}
