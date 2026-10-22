/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the functions to help with the user interface,
 * including the main function, and the functions to get user input and parse it.
 ********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vect.h"
#include "vectorstorage.h"
void run_interface(){
    vect *v = create_vector(10);
    if (v == NULL) {
        return;
    }
    char *tokens[6];
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
        while (p != NULL && count < 6) {
            tokens[count] = p;
            count++;
            p = strtok(NULL, " ,\t\n");
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
            } else if (strcmp(tokens[0], "list") == 0) {
                list();
            } else {
                vect result = findvect(tokens[0], v);
                if (strlen(result.name) > 0) {
                    printf("%s = %.2f, %.2f, %.2f\n", result.name, result.x, result.y, result.z);
                }
            }
        } else if (count == 2) {
            if (strcmp(tokens[0], "load") == 0) {
                const char *filepath = tokens[1];
                loadfile(filepath, &v);
            } else if (strcmp(tokens[0], "save") == 0) {
                const char *filepath = tokens[1];
                savefile(filepath, v);
            } else {
                printf("Invalid command. Type 'help' for a list of valid commands.\n");
            }
        } else if (count == 3) {
            if (strcmp(tokens[1], "+") == 0) {
                vect v1 = findvect(tokens[0], v);
                vect v2 = findvect(tokens[2], v);
                if (strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                    vect result = add(v1, v2);
                    printf("result = %.2f, %.2f, %.2f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "-") == 0) {
                vect v1 = findvect(tokens[0], v);
                vect v2 = findvect(tokens[2], v);
                if (strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                    vect result = subtract(v1, v2);
                    printf("result = %.2f, %.2f, %.2f\n", result.x, result.y, result.z);
                }
            } else if (strcmp(tokens[1], "*") == 0) {
                char *end;
                double s = strtod(tokens[0], &end);
                vect found;
                if (*end == '\0') {
                    found = findvect(tokens[2], v);
                } else {
                    found = findvect(tokens[0], v);
                    s = strtod(tokens[2], &end);
                    if (*end != '\0') {
                        printf("Expected a number!!!\n");
                        found.name[0] = '\0';
                    }
                }
                if (strlen(found.name) > 0) {
                    vect result = scalar_multiply(s, found);
                    printf("result = %.2f %.2f %.2f\n", result.x, result.y, result.z);
                }
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count == 4) {
            if (strcmp(tokens[1], "=") == 0) {
                vect current;
                strncpy(current.name, tokens[0], sizeof(current.name) - 1);
                current.name[sizeof(current.name) - 1] = '\0'; // Ensure null
                current.x = atof(tokens[2]);
                current.y = atof(tokens[3]);
                current.z = 0;
                addvect(current, v);
                printf("%s = %.2f %.2f %.2f\n", current.name, current.x, current.y, current.z);
            } else {
                printf("Not a valid command.\n");
            }
        } else if(count == 5) {
            if (strcmp(tokens[1], "=") != 0) {
                printf("Not a valid command\n");
            } else if (strcmp(tokens[3], "+") == 0 ||
                       strcmp(tokens[3], "-") == 0 ||
                       strcmp(tokens[3], "*") == 0) {
                vect result;
                if(strcmp(tokens[3], "+") == 0) {
                    vect v1 = findvect(tokens[2], v);
                    vect v2 = findvect(tokens[4], v);
                    if(strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                        result = add(v1, v2);
                        strncpy(result.name, tokens[0], sizeof(result.name) - 1);
                        result.name[sizeof(result.name) - 1] = '\0';
                        addvect(result, v);
                        printf("%s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                    }
                } else if (strcmp(tokens[3], "-") == 0) {
                    vect v1 = findvect(tokens[2], v);
                    vect v2 = findvect(tokens[4], v);
                    if(strlen(v1.name) > 0 && strlen(v2.name) > 0) {
                        result = subtract(v1, v2);
                        strncpy(result.name, tokens[0], sizeof(result.name) - 1);
                        result.name[sizeof(result.name) - 1] = '\0';
                        addvect(result, v);
                        printf("%s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                    }
                } else { // num * vec
                    char *end;
                    double s = strtod(tokens[2], &end);
                    if (*end == '\0') {
                        vect v1 = findvect(tokens[4], v);
                        if(strlen(v1.name) > 0) {
                            result = scalar_multiply(s, v1);
                            strncpy(result.name, tokens[0], sizeof(result.name) - 1);
                            result.name[sizeof(result.name) - 1] = '\0';
                            addvect(result, v);
                            printf("%s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                        }
                    } else { //vec * num
                        s = strtod(tokens[4], &end);
                        if (*end != '\0') {
                            printf("Exepected a number for scalar multiplication.\n");
                        } else {
                            vect v1 = findvect(tokens[2], v);
                            if(strlen(v1.name) > 0) {
                                result = scalar_multiply(s, v1);
                                strncpy(result.name, tokens[0], sizeof(result.name) - 1);
                                result.name[sizeof(result.name) - 1] = '\0';
                                addvect(result, v);
                                printf("%s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                            }
                        }
                    }
                }
            
            } else {
                vect result;
                strncpy(result.name, tokens[0], sizeof(result.name) - 1);
                result.name[sizeof(result.name) - 1] = '\0'; // Ensure null
                result.x = atof(tokens[2]);
                result.y = atof(tokens[3]);
                result.z = atof(tokens[4]);
                addvect(result, v);
                    printf("%s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);

            }
        } else {
            printf("Error!!!!!\n");
        }
    }
}