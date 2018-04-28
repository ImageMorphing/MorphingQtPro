#ifndef IMAGE_SEPERATOR_H
#define IMAGE_SEPERATOR_H

#include <iostream>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include "image_io_processor.h"

class image_seperator {
public:
    image_seperator(std::string);
    ~image_seperator();


    void sepe_image(std::string);

    void __check_path__();

private:
    std::string path;

    image_io_processor img_pro;
};


#endif // IMAGE_SEPERATOR_H
