#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"


#undef main

int window_height = 600;
int window_width = 1400;

// rendering basic shapes functions

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &Message_rect);

    // render frame
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &Message_rect);

    //SDL_RenderDrawRect(renderer, &Message_rect);

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Clean up
    SDL_DestroyTexture(Message);
    TTF_CloseFont(font);
    TTF_Quit();
}

void render_alt(SDL_Renderer *renderer, int x, int y, int l, int h, int num_items){//l and h are maximums
    render_line(renderer, x, y, l, 0);
    for(int i = 1; i< num_items;i++){
        render_line(renderer, x, y, h*i, 270);
        render_line(renderer, x+l, y, h*i, 270);
        render_line(renderer, x, y+(h*i), l, 0);
    }
}

void render_opt(SDL_Renderer *renderer, int x, int y, int l, int h){
    render_line(renderer, x, y, l, 0);
    render_line(renderer, x+l, y, h, 270);
    render_line(renderer, x, y+h, l, 0);
    render_line(renderer, x, y+h, h, 90);
}

void render_rec(SDL_Renderer *renderer, int x, int y, int l, int h){
    render_line(renderer, x, y, l, 0);
    render_line(renderer, x+l, y, h, 270);
    render_line(renderer, x, y+h, l, 0);
    render_arrow(renderer, x, y+h, h, 90);
}

// rendering the AST

int findSumOfMaxChildLengthsExcludingAlt(tree root) {
    if (root == NULL) {
        return 0;
    }

    // Initialize sum of max lengths to 0
    int sumOfMaxLengths = 1;

    // If the node is not ALTERNATIVE, calculate the sum of max lengths of its children
    if (root->type != ALTERNATIVE) {
        list* currentChild = root->children;
        while (currentChild != NULL) {
            tree childNode = (tree)(currentChild->child);
            int childLength = findSumOfMaxChildLengthsExcludingAlt(childNode);
            sumOfMaxLengths += childLength;
            currentChild = currentChild->nextNode;
        }
    }

    return sumOfMaxLengths;
}

void render_level(SDL_Renderer *renderer, tree root, int x, int y, int level){
    if (root == NULL) {
        return;
    }

    list *currentChild = root->children;
    // counting how many elements in one level
    int level_length = 0;
    while (currentChild != NULL) {
        level_length++;
        currentChild = currentChild->nextNode;
    }


    if (level == 0){
        int max_children = findSumOfMaxChildLengthsExcludingAlt(root);
        render_label(renderer, root->info, 20, 20, 10);
        render_arrow(renderer, x, y, max_children*200, 0);
    }
    if (level !=0) {
        switch (root->type) {
            case ID:
                render_label(renderer, root->info, 20, x + 10, y - 10);
                break;
            case LITERAL:
                render_label(renderer, root->info, 20, x + 10, y - 10);
                break;
            case RECURSSIVE:
                render_rec(renderer, x, y, (level_length*210), 150);
                x= x+10;
                y = y + 150;
                break;
            case OPTIONAL:
                render_opt(renderer, x, y, (level_length*200), 150);
                x = x + 10;
                y = y + 150;
                break;
            case ALTERNATIVE:
                render_alt(renderer, x, y,  200, 150, level_length);
                break;
            default:       
                break;
        }
    }
    // Recursively render children
    currentChild = root->children;
    if ((root->type!= ALTERNATIVE)){
        while (currentChild != NULL) {
            render_level(renderer, (tree)(currentChild->child), x, y, level + 1);
            x += 210;
            currentChild = currentChild->nextNode;
        }
    }
    if ((root->type == ALTERNATIVE)){
        while (currentChild != NULL) {
            render_level(renderer, (tree)(currentChild->child), x+10, y, level + 1);
            y += 150;
            currentChild = currentChild->nextNode;
        }
    }
}

void render_production(SDL_Renderer *renderer, tree root){
    render_level(renderer, root, 30, 60, 0);
}

//events

static int render_window(tree ast){
    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width, window_height,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowResizable(window, SDL_TRUE);
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
        render_production(renderer, ast);
        
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

    char input_ebnf[100];
    printf("saisie l'expression ebnf");
    fgets(input_ebnf, sizeof(input_ebnf), stdin);

    // Remove the newline character at the end, if present
    size_t len = strlen(input_ebnf);
    if (len > 0 && input_ebnf[len - 1] == '\n') {
        input_ebnf[len - 1] = '\0';
    }

    Token* parse_tree = lexer(input_ebnf);

    tree ast = parser(parse_tree);
    if(ast != NULL){
        render_window(ast);
    }

    return 0;
}
