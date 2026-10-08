/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the helper functions to store
 * vector data, functions include addvect, findvect, clear, and list.
 ********************/
#include <string.h>
#include "vectorstorage.h"
static vect vector_array[10]; //Array to hold the vectors
static int count = 0; //Counter to keep track of the number of vectors in the array
//Adds a vector to the vector array
void addvect(vect vnew) {
    for(int i = 0; i < count; i++) {
        if(strcmp(vector_array[i].name, vnew.name) == 0) {
            vector_array[i] = vnew;
            return;
        }
    }
    if(count < 10) {
        vector_array[count] = vnew;
        count++;
    } else {
        printf("Vector array is full, cannot add new vector. Use the clear command first\n");
    }

}
//Finds a vector in the vector array by name and returns it
vect findvect(char *name) {
    for(int i = 0; i < count; i++) {
        if(strcmp(vector_array[i].name, name) == 0) {
            return vector_array[i];
        }
    }
    printf("Could not find the vector %s\n", name);
    return (vect){"", 0, 0, 0}; // Return a default vector if not found
}
//Clears the vecotor array
void clear() {
    count = 0;
    memset(vector_array, 0, sizeof(vector_array));
}
//Lists all the vectors in the vector array
void list() {
    for(int i = 0; i < count; i++) {
        printf("%s = %f, %f, %f\n", vector_array[i].name, vector_array[i].x, vector_array[i].y, vector_array[i].z);
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
