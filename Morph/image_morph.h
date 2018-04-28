#ifndef IMAGE_MORPH_H
#define IMAGE_MORPH_H

#include <iostream>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include "image_util.h"
#include "image_meshwrap.h"
#include "image_io_processor.h"

void image_morph(const IplImage* I1,
                 const IplImage* I2,
                 const image_ptr M1,
                 const image_ptr M2,
                 int frame_num,
                 const std::string basename);

#endif // IMAGE_MORPH_H
