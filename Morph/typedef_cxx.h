#ifndef TYPEDEF_CXX_H
#define TYPEDEF_CXX_H

#include <iostream>

#define BW 0
#define MESH 1

typedef unsigned char uchar;

typedef struct {    /* image data structure  */
    int width;      /* image width  (# cols) */
    int height;     /* image height (# rows) */
    void *ch[2];    /* pointers to channels  */
} image_struct, *image_ptr;

#endif // TYPEDEF_CXX_H
