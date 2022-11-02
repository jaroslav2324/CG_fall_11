#include "Application.h"


Application::Application() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        cout << "Error with SDL_Init" << endl;

    SDL_Window* window = SDL_CreateWindow("KG_Curs", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    ZBuffer buffer;
    Parallelepiped* par = new Parallelepiped();
    Pyramid* pyr = new Pyramid();


    buffer.renderBuffer(renderer, par, pyr);

    //SDL_Delay(20000);


    while(true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            bool changed = false;
            // check for messages
            switch (event.type) {
                // exit if the window is closed
            case SDL_QUIT:

                delete par;
                delete pyr;

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);

                SDL_Quit();

                return; 

              // check for keypresses
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym) {
                case SDLK_w:
                    par->moveAlongY(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_s:
                    par->moveAlongY(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_a:
                    par->moveAlongX(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_d:
                    par->moveAlongX(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_q:
                    par->moveAlongZ(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_e:
                    par->moveAlongZ(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_z:
                    par->rotateAroundX(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_x:
                    par->rotateAroundY(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_c:
                    par->rotateAroundZ(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_r:
                    par->rotateAroundX(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_f:
                    par->rotateAroundY(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_v:
                    par->rotateAroundZ(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_t:
                    par->scale(INCREASE_SCALE_VALUE);
                    changed = true;
                    break;
                case SDLK_g:
                    par->scale(DECREASE_SCALE_VALUE);
                    changed = true;
                    break;
                case SDLK_u:
                    pyr->moveAlongY(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_j:
                    pyr->moveAlongY(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_h:
                    pyr->moveAlongX(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_k:
                    pyr->moveAlongX(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_y:
                    pyr->moveAlongZ(-SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_i:
                    pyr->moveAlongZ(SHIFT_VALUE);
                    changed = true;
                    break;
                case SDLK_n:
                    pyr->rotateAroundX(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_m:
                    pyr->rotateAroundY(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_COMMA:
                    pyr->rotateAroundZ(ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_p:
                    pyr->rotateAroundX(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_SEMICOLON :
                    pyr->rotateAroundY(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_PERIOD:
                    pyr->rotateAroundZ(-ROTATE_VALUE);
                    changed = true;
                    break;
                case SDLK_LEFTBRACKET:
                    pyr->scale(INCREASE_SCALE_VALUE);
                    changed = true;
                    break;
                case SDLK_RIGHTBRACKET:
                    pyr->scale(DECREASE_SCALE_VALUE);
                    changed = true;
                    break;
                default:
                    break;
                }
            }

            if (changed)
                buffer.renderBuffer(renderer, par, pyr);
        }
    }
}
