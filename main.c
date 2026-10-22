/*********************
 * Author: Hunter Vassar
 * Date: 10/13/2026
 * Description: This is the main class for the program, simply checks 
 * for the -h argument from the user and then runs the run_interface();
 * function.
 * Compile: make
 * Executable: main
 ********************/
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "vectorstorage.h"

int main (int argc, char *argv[]) {
    if (argc > 1) {
        if(strcmp(argv[1], "-h") == 0) {
            help();
            return 1;
        } else {
            printf("Unknow option, please use -h for help\n");
            return 0;
        }
    }
    run_interface();
    return 1;
}