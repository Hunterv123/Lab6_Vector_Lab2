/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Initiates the helper functions to store
 * vector data, functions include addvect, findvect, clear, and list.
 ********************/
#ifndef VECTORSTORAGE_H
#define VECTORSTORAGE_H

#include "vectormath.h"
//Adds a vector to the vector array
void addvect(vect vnew, vect *vector);
//Finds a vector in the vector array by name and returns it
vect findvect(char *name, vect *vector);
//Clears the vecotor array
void clear();
//Lists all the vectors in the vector array
void list();
//Prints out a quick help menu for the user to see what commands are available
void help();
//Allows the users to export there list of vectors to a csv file
void savefile(const char *filepath, vect *vector);
//Allows users to load vectors in from a csv file 
void loadfile(const char* filepath, vect **vector);
vect* create_vector(int INITIAL_CAPACITY);



#endif