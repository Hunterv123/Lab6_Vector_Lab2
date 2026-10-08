/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the functions to help with the user interface,
 *  including the main function, and the functions to get user input and parse it.
 ********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector_struct.h"
#include "vectorstorage.h"
void run_interface(){
    char *tokens[5];
    char input[100]; // buffer to hold user input
    int count;
    while(1) {
        printf("minimat> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }
        char *p = strtok(input, " ,\t\n");
        count = 0;
        while (p != NULL && count < 5) {
            tokens[count] = p;
            count++;
            p = strtok(NULL, " ,\t\n");
        }
        if (count == 0) {
            continue; // no input, prompt again
        } else if (count == 1) {
            if (strcmp(tokens[0], "quit") == 0) {
                printf("Exiting the program.\n");
                break;
            } else if (strcmp(tokens[0], "help") == 0) {
                help();
            } else if (strcmp(tokens[0], "clear") == 0) {
                clear();
            } else if (strcmp(tokens[0], "list") == 0) {
                list();
            } else {
                vect v = findvect(tokens[0]);
                if (strlen(v.name) > 0) {
                    printf("%s = %.2f, %.2f, %.2f\n", v.name, v.x, v.y, v.z);
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
                    printf("result = %.2f, %.2f, %.2f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "-") == 0) {
                vect v1 = findvect(tokens[0]);
                vect v2 = findvect(tokens[2]);
                if (strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                    vect result = subtract(v1, v2);
                    printf("result = %.2f, %.2f, %.2f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "*") == 0) {
                char *end;
                double s = strtod(tokens[0], &end);
                vect v;
                if (*end == '\0') {
                    v = findvect(tokens[2]);
                } else {
                    v = findvect(tokens[0]);
                    s = strtod(tokens[2], &end);
                    if (*end != '\0') {
                        printf("Expected a number!!!\n");
                        v.name[0] = '\0';
                    }
                }
                if (strlen(v.name) > 0) {
                    vect result = scalar_multiply(s, v);
                    printf("result = %.2f %.2f %.2f\n", result.x, result.y, result.z);
                }
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count == 4) {
            if (strcmp(tokens[1], "=") == 0) {
                vect v;
                strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                v.name[sizeof(v.name) - 1] = '\0'; // Ensure null
                v.x = atof(tokens[2]);
                v.y = atof(tokens[3]);
                v.z = 0;
                addvect(v);
                printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count == 5) {
            if (strcmp(tokens[1], "=") != 0) {
                printf("Not a valid command\n");
            } else if (strcmp(tokens[3], "+") == 0 ||
                       strcmp(tokens[3], "-") == 0 ||
                       strcmp(tokens[3], "*") == 0) {
                vect v;
                if(strcmp(tokens[3], "+") == 0) {
                    vect v1 = findvect(tokens[2]);
                    vect v2 = findvect(tokens[4]);
                    if(strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                        v = add(v1, v2);
                        strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                        v.name[sizeof(v.name) - 1] = '\0';
                        addvect(v);
                        printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                    }
                } else if (strcmp(tokens[3], "-") == 0) {
                    vect v1 = findvect(tokens[2]);
                    vect v2 = findvect(tokens[4]);
                    if(strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                        v = subtract(v1, v2);
                        strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                        v.name[sizeof(v.name) - 1] = '\0';
                        addvect(v);
                        printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                    }
                } else { // num * vec
                    char *end;
                    double s = strtod(tokens[2], &end);
                    if (*end == '\0') {
                        vect v1 = findvect(tokens[4]);
                        if(strlen(v1.name) > 0) {
                            v = scalar_multiply(s, v1);
                            strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                            v.name[sizeof(v.name) - 1] = '\0';
                            addvect(v);
                            printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                        }
                    } else { //vec * num
                        s = strtod(tokens[4], &end);
                        if (*end != '\0') {
                            printf("Exepected a number for scalar multiplication.\n");
                        } else {
                            vect v1 = findvect(tokens[2]);
                            if(strlen(v1.name) > 0) {
                                v = scalar_multiply(s, v1);
                                strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                                v.name[sizeof(v.name) - 1] = '\0';
                                addvect(v);
                                printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                            }
                        }
                    }
                }
            
            } else {
                vect v;
                strncpy(v.name, tokens[0], sizeof(v.name) - 1);
                v.name[sizeof(v.name) - 1] = '\0'; // Ensure null
                v.x = atof(tokens[2]);
                v.y = atof(tokens[3]);
                v.z = atof(tokens[4]);
                addvect(v);
                    printf("%s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);

            }
        }
    }
}