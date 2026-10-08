/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Initiates the functions to perform vector math operations
 ********************/
#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "vector_struct.h"
vect add(vect v1, vect v2);
vect subtract(vect v1, vect v2);
vect scalar_multiply(double scalar, vect v1);

#endif