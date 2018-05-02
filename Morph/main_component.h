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

    IplImage* execute_by_morph(std::string scr_image_name,
                      std::string tgt_image_name,
                      unsigned int mesh_width,
                      unsigned int mesh_height,
                      float* cor_x1,
                      float* cor_y1,
                      float* cor_x2,
                      float* cor_y2);
private:
    std::string file_addr;
    std::string frame_base_name;
    unsigned int frame_num;

    image_io_processor img_pro;
    image_util img_utl;
    image_seperator img_sep;
};


#endif // MAIN_COMPONENT_H
