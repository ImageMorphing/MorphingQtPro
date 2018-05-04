#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <iostream>

#include "image_util.h"
#include "image_morph.h"
#include "image_io_processor.h"

class main_component {
public:
    main_component(std::string file_addr, std::string base_name, unsigned int frame_num);
    main_component(std::string base_name, unsigned int frame_num);

    void execute(std::string scr_image_name, std::string tgt_image_name);
private:
    std::string file_addr;
    std::string frame_base_name;
    unsigned int frame_num;

    image_io_processor img_pro;
    image_util img_utl;
};


#endif // MAIN_COMPONENT_H
