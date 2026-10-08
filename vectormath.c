/*********************
 * Author: Hunter Vassar
 * Date: 10/01/2026
 * Description: Defines the functions to perform vector math operations
 * Only need to do add, subtract, and scalar multiply.
 ********************/

#include "vector_struct.h"
#include "vectormath.h"
vect add(vect v1, vect v2) {
    vect result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;

}

vect subtract(vect v1, vect v2) {
    vect result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

vect scalar_multiply(double scalar, vect v1) {
    vect result;
    result.x = scalar * v1.x;
    result.y = scalar * v1.y;
    result.z = scalar * v1.z;
    return result;
}


