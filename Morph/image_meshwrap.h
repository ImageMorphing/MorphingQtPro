#ifndef IMAGE_MESHWRAP_H
#define IMAGE_MESHWRAP_H

#include <iostream>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include "image_util.h"
#include "catmullrom.h"
#include "typedef_cxx.h"

void image_meshwarp(const IplImage* I1, const image_ptr M1, const image_ptr M2, const IplImage* I2);

void resample(char *src, int len, int offst, float *xmap, char *dst);

#endif // IMAGE_MESHWRAP_H
