#ifndef IMAGE_MERGER_H
#define IMAGE_MERGER_H

#include <iostream>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include "image_io_processor.h"

class image_merger {
public:
    image_merger(std::string);
    ~image_merger();


    void merg_image(std::string);

    IplImage* get_merged_image();

    void __check_path__();

private:
    std::string path;

    IplImage* res_img;

    image_io_processor img_pro;
};


#endif // IMAGE_MERGER_H
