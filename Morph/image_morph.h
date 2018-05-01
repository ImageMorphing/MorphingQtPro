#ifndef IMAGE_MORPH_H
#define IMAGE_MORPH_H

#include <iostream>
#include <cassert>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include <QMessageBox>

#include "image_util.h"
#include "image_meshwarp.h"
#include "image_io_processor.h"

bool image_morph(const IplImage* I1,
                 const IplImage* I2,
                 const image_ptr M1,
                 const image_ptr M2,
                 int frame_num,
                 const std::string basename);

void execute_error_hint_morph(std::string text, std::string informative_text, std::string detailed_text = "");

#endif // IMAGE_MORPH_H
