#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <lexer.h>
#include <parser.h>
#include <mapper.h>

#undef main


void red() {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void green(){
  printf("\033[0;32m");
}

void reset() {
  printf("\033[0m");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    
    
    char input_ebnf[100];
    yellow();
    printf("-------- saisie l'expression EBNF -----------\n");
    printf(">> ");
    reset();
    
    memset(input_ebnf, 0, sizeof(input_ebnf));
    fgets(input_ebnf, sizeof(input_ebnf), stdin);

    // Remove the newline character at the end, if present
    size_t len = strlen(input_ebnf);
    if (len > 0 && input_ebnf[len - 1] == '\n') {
        input_ebnf[len - 1] = '\0';
    }

    red();
    Token* parse_tree = lexer(input_ebnf);
    reset();
    
    if (parse_tree != NULL){
      red();
      tree ast = parser(parse_tree);
      reset();
    
      if(ast != NULL){
          green();
          printf("\n--------------- SUCCESS!!---------------\n");
          reset();
          int flag = 0;
          int choix;
          while(flag == 0){
            yellow();
            printf("\n--------choisie un mode d'affichage:----------\n");
            printf("1. afficher le diagrammme étant que arbre\n");
            printf("2. afficher le diagramme graphique\n");
            printf("3. quit\n");
            printf(">> ");
            reset();

            int result = scanf("%d", &choix);

            if (result != 1) {
                printf("\n Invalid input. Please enter an integer.");
                clearInputBuffer();
            } else {          
              switch (choix){
                case 1: 
                  displayTree(ast);
                  break;
                case 2: 
                  render_window(ast);
                  break;
                case 3:
                  green();
                  printf("\n----------- quitter ----------------");
                  reset();
                  flag = 1;
                  break;
                default:
                  
                  break;
              }
            }
          }

      }
    }
  
    return 0;
}