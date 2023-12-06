#include <stdio.h>
#include <stdlib.h>
#include "C:/Users/lenovo/Documents/insea2023/compilateur/mapper.h"

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    // Call the render_app function
    render_app(argc, argv);

    return 0;
}