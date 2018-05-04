#ifndef IMAGE_MERGER_H
#define IMAGE_MERGER_H

#include <iostream>

#include <imgproc.hpp>
#include <highgui.hpp>
#include <core/utility.hpp>

#include <QMessageBox>

#include "image_io_processor.h"

class image_merger {
public:
    image_merger(std::string);
    image_merger();
    ~image_merger();


    bool merg_image(std::string);

    IplImage* get_merged_image();

    void __check_path__();

private:
    std::string path;

    IplImage* res_img;

    image_io_processor img_pro;

    void execute_error_hint(std::string, std::string, std::string detailed_text = "");
};


#endif // IMAGE_MERGER_H
