/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the functions to help with the user interface,
 *  including the main function, and the functions to get user input and parse it.
 ********************/
#include <stdio.h>
#include <string.h>
#include "vector_struct.h"
#include "vectorstorage.h"
void run_interface(){
    char *tokens[5];
    char input[100]; // buffer to hold user input
    int count;
    while(1) {
        printf("minimat> ");
        fgets(input, sizeof(input), stdin);
        char *p = strtok(input, " \n");
        count = 0;
        while (p != NULL && count < 5) {
            tokens[count] = p;
            count++;
            p = strtok(NULL, " \n");
        }
        if (count == 0) {
            continue; // no input, prompt again
        } else if (count == 1) {
            if (strcmp(tokens[0], "exit") == 0) {
                printf("Exiting the program.\n");
                break;
            } else if (strcmp(tokens[0], "help") == 0) {
                help();
            } else if (strcmp(tokens[0], "clear") == 0) {
                clear();
            } else {
                vect v = findvect(tokens[0]);
                if (strlen(v.name) > 0) {
                    printf("%s = %f, %f, %f\n", v.name, v.x, v.y, v.z);
                }
            }
        } else if (count == 2) {
            printf("Invalid command. Type 'help' for a list of valid commands.\n");
        } else if (count == 3) {
            if (strcmp(tokens[1], "+") == 0) {
                vect v1 = findvect(tokens[0]);
                vect v2 = findvect(tokens[2]);
                if (strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                    vect result = add(v1, v2);
                    printf("result = %f, %f, %f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "-") == 0) {
                vect v1 = findvect(tokens[0]);
                vect v2 = findvect(tokens[2]);
                if (strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                    vect result = subtract(v1, v2);
                    printf("result = %f, %f, %f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "*") == 0) {
                double scalar = atof(tokens[0]);
                vect v2 = findvect(tokens[2]);
                if (strlen(v2.name) > 0) {
                    vect result = scalar_multiply(scalar, v2);
                    printf("result = %f, %f, %f\n", result.x, result.y, result.z);
                }
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count = 4) {
            if (strcmp(tokens[1], "=") == 0) {
                vect v;
                strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                v.name[sizeof(v.name) - 1] = '\0'; // Ensure null
                v.x = atof(tokens[2]);
                v.y = atof(tokens[3]);
                v.z = 0;
                addvect(v);
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count = 5) {
            if (strcmp(tokens[1], "=") == 0) {
                ve
            }
        }
    }
}