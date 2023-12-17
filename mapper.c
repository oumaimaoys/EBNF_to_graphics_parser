#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "tree.h"


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
        x1 = x;
        x2= x;
        y1 = y;
        y2 = y - length;
    }
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void render_arrow(SDL_Renderer *renderer, int x, int y, int length, int angle){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    int len = length - 10;
    // Render a line
    int x1, x2, y1, y2;
    int a, b, c, d, e, f;
    if (angle == 0){ // horizontal
        x1 = x;
        y1 = y;
        y2 = y;
        x2 = x + len;
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
        y2 = y + len;
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
        y2 = y - len;
        a = x1 - 10;
        c = x1 + 10;
        b = y2;
        d = y2;
        e = x1;
        f = y2 - 10;
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

void render_label(SDL_Renderer *renderer, char* text, int size, int x, int y){ // return int instead maybe for error detection

    TTF_Init();
    // font , size and color
    TTF_Font* font = TTF_OpenFont("C:\\Users\\lenovo\\Documents\\insea2023\\compilateur\\roboto.ttf", size);

    SDL_Color Black = {0, 0, 0};

    // Add spaces to the beginning and end
    size_t originalLength = strlen(text);
    size_t newLength = originalLength + 2; // Add 2 for spaces
    // Allocate memory for the new string
    char* newText = (char*)malloc((newLength + 1) * sizeof(char)); // +1 for null terminator
    // Add space at the beginning
    newText[0] = ' ';
    // Copy the original text
    strcpy(newText + 1, text);
    // Add space at the end
    newText[newLength - 1] = ' ';
    // Null-terminate the new string
    newText[newLength] = '\0';

    // surface, because text can only be rendered on a surface
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, newText, Black);
    // create a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int h = surfaceMessage->h;
    int w = surfaceMessage->w;

    // create rectangle
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  
    Message_rect.y = y;
    Message_rect.w = w;
    Message_rect.h = h;

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

void render_alt(SDL_Renderer *renderer){}

void render_opt(SDL_Renderer *renderer){}

void render_rec(SDL_Renderer *renderer){}

void render_exp(SDL_Renderer *renderer){}

void render_level(SDL_Renderer *renderer, tree root, int level){
    if (root == NULL) {
        return;
    }

    if (level == 0){
        render_label(renderer, root->info, 20, 0, 0);
        render_arrow(renderer, 20, 50, 700, 0);
    }
    else{
        switch (root->type) {
            case ID:
                render_label(renderer, root->info, 20, 0, 0);
                break;
            case LITERAL:
                render_label(renderer, root->info, 20, 0, 0);
                break;
            case RECURSSIVE:
                
                break;
            case OPTIONAL:
                
                break;
            case ALTERNATIVE:
                
                break;
            case PARENT:
                
                break;
            default:       
                break;
        }
    }


    // Recursively display children
    list *currentChild = root->children;
    while (currentChild != NULL) {
        render_level(renderer, (tree)(currentChild->child), level + 1);
        currentChild = currentChild->nextNode;
    }
}

void render_production(SDL_Renderer *renderer, tree root){
    render_level(renderer, root, 0);
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
        //render_label(renderer, "hellothere", 20, 10,10);
        //render_arrow(renderer, 200, 200, 500, 0);
        //render_line(renderer, 400, 400, 200, 90);
        //render_arrow(renderer, 300, 400, 200, 90);
        //render_line(renderer, 300, 400, 100, 0);
        
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
