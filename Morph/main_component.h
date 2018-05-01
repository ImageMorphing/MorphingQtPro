#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <iostream>

#include "image_util.h"
#include "image_morph.h"
#include "image_seperator.h"
#include "image_io_processor.h"

class main_component {
public:
    main_component(std::string file_addr, std::string base_name, unsigned int frame_num);

    IplImage* execute(std::string scr_image_name, std::string tgt_image_name);
private:
    std::string file_addr;
    std::string frame_base_name;
    unsigned int frame_num;

    image_io_processor img_pro;
    image_util img_utl;
    image_seperator img_sep;
};


#endif // MAIN_COMPONENT_H
