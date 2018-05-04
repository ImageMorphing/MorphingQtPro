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
    image_seperator();
    ~image_seperator();


    bool sepe_image(std::string);

    void __check_path__();

private:
    std::string path;

    image_io_processor img_pro;

    void execute_error_hint(std::string, std::string, std::string detailed_text = "");
};


#endif // IMAGE_SEPERATOR_H
