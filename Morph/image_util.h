#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include <iostream>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include "image_io_processor.h"

#include "typedef_cxx.h"

class image_util {
public:
    image_util(std::string);
    ~image_util();

    image_ptr read_image_as_bw(IplImage* img);
    image_ptr read_mesh(std::string file_name);

    void save_image_as_bw(image_ptr img, std::string file_name);
    void save_mesh(image_ptr mes, std::string file_name);

    image_ptr allo_image(int width, int height, int type);
    void free_image(image_ptr ptr);

private:
    image_io_processor img_pro;

    std::string path;

    image_ptr tran_image(IplImage*);
    image_ptr tran_image(FILE*);

    void execute_error_hint(std::string, std::string, std::string detailed_text = "");
};


#endif // IMAGE_UTIL_H
