#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>


#undef main

void render_line(SDL_Renderer *renderer,  int x, int y, int length, int angle){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    int x1, x2, y1, y2 = 0;
    if (angle == 0){ // horizontal
        x1 = x;
        y1= y ;
        y2 = y;
        x2 = x + length;
    }
    else if (angle == 270){ // vertical
        x1 = x;
        x2= x;
        y1 = y;
        y2 = y + length;
    }
    else if (angle == 90){

    }
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void render_arrow(SDL_Renderer *renderer, int x, int y, int length, int angle){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    // Render a line
    int x1, x2, y1, y2;
    int a, b, c, d, e, f;
    if (angle == 0){ // horizontal
        x1 = x;
        y1 = y;
        y2 = y;
        x2 = x + length;
        a = x2;
        c = x2;
        b = y1 - 10;
        d = y1 + 10;
        e = x2 + 10;
        f = y2;
    }
    else if (angle == 270){ // vertical
        x1 = x;
        x2= x;
        y1 = y;
        y2 = y + length;
        a = x1 - 10;
        c = x1 + 10;
        b = y2;
        d = y2;
        e = x1;
        f = y2 + 10;
    }
    else if (angle == 90){
        x1 = x;
        x2= x;
        y1 = y;
        y2 = y + length;
        a = x1 - 10;
        c = x1 + 10;
        b = y2;
        d = y2;
        e = x1;
        f = y2 + 10;
    }
    
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_Vertex triangleVertex[3]= {
        {{ a, b}, { 0, 0, 0, 255 }, { 0.f, 0.f }},
        {{ c, d },{ 0,0,0, 255 },{ 0.f, 0.f }},
        {{ e, f }, { 0,0,0, 255 }, { 0.f, 0.f }}
    };
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderGeometry(renderer, NULL, triangleVertex, 3, NULL, 0);
    
}


void render_label(SDL_Renderer *renderer, char* text){ // return int instead maybe for error detection

    TTF_Init();
    // font , size and color
    TTF_Font* font = TTF_OpenFont("C:\\Users\\lenovo\\Documents\\insea2023\\compilateur\\roboto.ttf", 24);

    SDL_Color Black = {0, 0, 0};

    // surface, because text can only be rendered on a surface
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, Black);
    // create a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    // create rectangle
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 200;  
    Message_rect.y = 100;
    Message_rect.w = 200;
    Message_rect.h = 100;

    // Render the filled rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // White color for the rectangle
    SDL_RenderDrawRect(renderer, &Message_rect);

    //SDL_RenderDrawRect(renderer, &Message_rect);

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Clean up
    SDL_DestroyTexture(Message);
    TTF_CloseFont(font);
    TTF_Quit();
}

static int render_window(){
    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }
    // create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 225,225,225,255);
    SDL_RenderClear(renderer);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Main event loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // rendering
        //render_label(renderer, "hello");
        render_line(renderer, 200, 200, 500, 0);
        render_line(renderer, 400, 400, 200, 90);
        render_arrow(renderer, 300, 400, 200-10, 90);
        render_line(renderer, 300, 400, 100, 0);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    render_window();


    return 0;
}
