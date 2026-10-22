/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the helper functions to store
 * vector data, functions include addvect, findvect, clear, and list.
 ********************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vectorstorage.h"
static int size = 10; 
static int count = 0; //Counter to keep track of the number of vectors in the array
//Allows users to load vectors in from a csv file 

vect* create_vector(int INITIAL_CAPACITY) {
    vect *vector = malloc(INITIAL_CAPACITY * sizeof(vect));
    if (vector == NULL) {
        free(vector);
        perror("Error creating memory in program");
    }
    return vector;
}
void loadfile(const char* filepath, vect **vector) {
    char buffer[100];
    FILE *fd = fopen(filepath, "r");
    if (fd == NULL) {
        perror("Error opening the file");
        return;
    }
    while(fgets(buffer, sizeof(buffer), fd) != NULL) {
        if(count + 1 > size) {
            size *= 2;
            vect *temp = realloc(*vector, size * sizeof(vect));
            *vector = temp;
        }
        vect *v = *vector;
        char *tokens[4];
        int token_count = 0;
        char *p = strtok(buffer, " ,\t\n");
        count = 0;
        while (p != NULL && count < 6) {
            tokens[count] = p;
            token_count++;
            p = strtok(NULL, " ,\t\n");
        }
        if (token_count < 2) {
            continue;
        }
        strncpy(v[count].name, tokens[0], sizeof(v[count].name) - 1);
        v[count].name[sizeof(v[count].name) - 1] = '\0'; // Ensure null
        v[count].x = atof(tokens[1]);
        v[count].y = token_count > 2 ? atof(tokens[2]) : 0.0;
        v[count].z = token_count > 3 ? atof(tokens[3]) : 0.0;
        count++;
    }
    fclose(fd);
}

void savefile(const char* filepath, vect *vector) {
    FILE *fd = fopen(filepath, "w");
    if (fd == NULL) {
        perror("Error saving to the specified file");
        return;
    }
    for(int i = 0; i < count; i++) {
        fprintf(fd, "%s,%.2f,%.2f,%.2f\n", vector[i].name, vector[i].x, vector[i].y, vector[i].z);
    }
    fclose(fd);
    printf("Successfully saved\n");
}
//Adds a vector to the vector array
void addvect(vect vnew, vect *vector) {
    for(int i = 0; i < count; i++) {
        if(strcmp(vector[i].name, vnew.name) == 0) {
            vector[i] = vnew;
            return;
        }
    }
    if(count + 1 > size) {
        size *= 2;
        vect *temp = realloc(vector, size * sizeof(vect));
        vector = temp;
    }
    vector[count] = vnew;

    count++;

}
//Finds a vector in the vector array by name and returns it
vect findvect(char *name, vect *vector) {
    for(int i = 0; i < count; i++) {
        if(strcmp(vector[i].name, name) == 0) {
            return vector[i];
        }
    }
    printf("Could not find the vector %s\n", name);
    return (vect){"", 0, 0, 0}; // Return a default vector if not found
}
//Clears the vecotor array
void clear(vect *vector) {
    count = 0;
    free(vector);
}
//Lists all the vectors in the vector array
void list(vect *vector) {
    for(int i = 0; i < count; i++) {
        printf("%s = %.2f, %.2f, %.2f\n", vector[i].name, vector[i].x, vector[i].y, vector[i].z);
    }
}
//Prints out a quick help menu for the user to see what commands are available
void help() {
    printf("First make a type in vector name, the its x, y, and z components.\n");
    printf("Once you have a couple of vectors you can do the follwoing:\n");
    printf("a - prints out the vector\n");
    printf("a + b - adds the two vecotrs and prints out the result\n");
    printf("c = a + b - adds the two vecors and stores the result in a new vector c\n");
    printf("a - b - subtracts vector a from vector b and prints out the result\n");
    printf("5 * b - multiplies vector b by 5 and prints out the result\n");
    printf("Some commands you can run:\n");
    printf("help - Show this help menu\n");
    printf("clear - Clears the vector array\n");
    printf("list - Lists all the vectors in the vector array, max of 10\n");
}
