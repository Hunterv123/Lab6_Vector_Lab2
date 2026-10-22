# Lab6_Vector_Lab2 Hunter Vassar

## Description
    - This program essentialy acts as a basic vector calculator, allowing the user to perfrom multiple vector calculations. Supported calculations include, adding two vectors, subtracting two vectors, and multiplying a vector by a scalar.

## Building
    - Make sure to clone the repo with git clone
    - Run 'make' to compile

## Running the program
    - ./main -h, prints help menu
    - ./main starts interactive mode

## Supported Commands
    - list: lists all the vectors in memory
    - quit: exits the program
    - clear: clears the list of vectors in memory
    - to add a vector, simply list a vector name with its x, y, and z components

## Dynamic Memory useage
    - This program makes use of dynamic memory by allocating an inital memory space of 10 vectors. Once the user stores a vector one less than the initial allocated memory, memory is then doubled to allow the user to input more vectors. Upon clear, the memory is freed and reset back to only 10 vectors.


Test for lab