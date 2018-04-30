#ifndef IMAGE_MESHWRAP_H
#define IMAGE_MESHWRAP_H

#include <iostream>
#include <cassert>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include <QMessageBox>

#include "image_util.h"
#include "catmullrom.h"
#include "typedef_cxx.h"

void image_meshwarp(const IplImage* I1, const image_ptr M1, const image_ptr M2, const IplImage* I2);

void resample(char *src, int len, int offst, float *xmap, char *dst);

void execute_error_hint_meshwarp(std::string text, std::string informative_text, std::string detailed_text = "");

#endif // IMAGE_MESHWRAP_H
