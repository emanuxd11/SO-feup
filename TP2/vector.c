#include "vector.h"
#include <stdlib.h>

vector* vector_new(double x, double y, double z) {
    vector *ret = malloc(sizeof(vector));
    ret->x = x;
    ret->y = y;
    ret->z = z;

    return ret;
}

vector* vector_add(vector *v1, vector *v2) {
    vector *sum = vector_new(v1->x, v1->y, v1->z);

    sum->x += v2->x;
    sum->y += v2->y;
    sum->z += v2->z;

    return sum;
}

vector* vector_sub(vector *v1, vector *v2) {
    vector *diff = vector_new(v1->x, v1->y, v1->z);

    diff->x -= v2->x;
    diff->y -= v2->y;
    diff->z -= v2->z;

    return diff;
}

vector* vector_scale(double scale, vector* v) {
    vector *scaled_v = vector_new(v->x, v->y, v->z);

    scaled_v->x *= scale;
    scaled_v->y *= scale;
    scaled_v->z *= scale;

    return scaled_v;
}

vector* vector_vprod(vector *v1, vector *v2) {
    return NULL;
}

double vector_sprod(vector *v1, vector *v2) {
    return 0;
}

double vector_mod(vector* v) {
    return 0;
}
