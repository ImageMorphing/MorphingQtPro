#include "image_merger.h"

image_merger::image_merger(std::string file_addr): img_pro(file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if (file_addr[file_addr.size() - 1] != '/') {
        file_addr += '/';
    }
    path = file_addr;
    res_img = 0;
}

image_merger::~image_merger() {}

void image_merger::merg_image(std::string img_name) {
    IplImage *r_channel = img_pro.load_image_as_object(path + "r.bw"),
             *g_channel = img_pro.load_image_as_object(path + "g.bw"),
             *b_channel = img_pro.load_image_as_object(path + "b.bw");

    res_img = img_pro.init_image(cvGetSize(r_channel), IPL_DEPTH_8U, 3);

    img_pro.gene_image(r_channel, g_channel, b_channel, res_img);

    img_pro.save_image(img_name, res_img);
}

IplImage* image_merger::get_merged_image() {
    if (res_img) {
        return res_img;
    }
    return (IplImage *)0;
}

void image_merger::__check_path__() {
    std::cout << stderr << "Path: " << path << std::endl;
    exit(9);
}

