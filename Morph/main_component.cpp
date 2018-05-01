#include "main_component.h"


main_component::main_component(std::string file_addr, std::string base_name, unsigned int frame_num)
    try :img_pro(file_addr), img_utl(file_addr) {
        this->file_addr = file_addr;
        if (file_addr.empty()) {
            std::cout << stderr << "Empty Str Received" << std::endl;
            throw std::string("Received empty string as file path");
        }
        if (base_name.empty()) {
            std::cout << stderr << "Empty Str Received" << std::endl;
            throw std::string("Received empty string as basename");
        }
        if (file_addr[file_addr.size() - 1] != '/') {
            this->file_addr += '/';
        }
        this->frame_base_name = base_name;
        this->frame_num = frame_num;
    } catch (std::string err_log) {
        throw err_log;
    }

void main_component::execute(std::string scr_image_name, std::string tgt_image_name) {
    IplImage *scr_image, *tgt_image,
             *r_channel_src, *g_channel_src, *b_channel_src,
             *r_channel_tgt, *g_channel_tgt, *b_channel_tgt;
    image_ptr I_r_src, I_g_src, I_b_src,
              I_r_tgt, I_g_tgt, I_b_tgt;
    image_ptr M1, M2;

    try {
        scr_image = img_pro.load_image(scr_image_name);
        tgt_image = img_pro.load_image(tgt_image_name);
    } catch (std::string err_log) {
        throw std::string("MAIN_COMPONENT Catch: ") + err_log;
    }

    try {
        r_channel_src = img_pro.init_image(cvGetSize(scr_image), IPL_DEPTH_8U, 1);
        g_channel_src = img_pro.init_image(cvGetSize(scr_image), IPL_DEPTH_8U, 1);
        b_channel_src = img_pro.init_image(cvGetSize(scr_image), IPL_DEPTH_8U, 1);
        r_channel_tgt = img_pro.init_image(cvGetSize(tgt_image), IPL_DEPTH_8U, 1);
        g_channel_tgt = img_pro.init_image(cvGetSize(tgt_image), IPL_DEPTH_8U, 1);
        b_channel_tgt = img_pro.init_image(cvGetSize(tgt_image), IPL_DEPTH_8U, 1);
    } catch (std::string err_log) {
        throw std::string("MAIN_COMPONENT Catch: ") + err_log;
    }
    cvSplit(scr_image, b_channel_src, g_channel_src, r_channel_src, NULL);
    cvSplit(tgt_image, b_channel_tgt, g_channel_tgt, r_channel_tgt, NULL);

    try {
        I_r_src = img_utl.read_image_as_bw(r_channel_src);
        I_g_src = img_utl.read_image_as_bw(g_channel_src);
        I_b_src = img_utl.read_image_as_bw(b_channel_src);
        I_r_tgt = img_utl.read_image_as_bw(r_channel_tgt);
        I_g_tgt = img_utl.read_image_as_bw(g_channel_tgt);
        I_b_tgt = img_utl.read_image_as_bw(b_channel_tgt);
    } catch (std::string err_log) {
        throw std::string("MAIN_COMPONENT Catch: ") + err_log;
    }

    try {
        M1 = img_utl.read_mesh("1.mesh");
        M2 = img_utl.read_mesh("2.mesh");
    } catch (std::string err_log) {
        throw std::string("MAIN_COMPONENT Catch: ") + err_log;
    }

    if (!image_morph(r_channel_src, r_channel_tgt, M1, M2, frame_num, frame_base_name))
        throw std::string("MAIN_COMPONENT Error: image_morph failed");
    if (!image_morph(g_channel_src, g_channel_tgt, M1, M2, frame_num, frame_base_name))
        throw std::string("MAIN_COMPONENT Error: image_morph failed");
    if (!image_morph(b_channel_src, b_channel_tgt, M1, M2, frame_num, frame_base_name))
        throw std::string("MAIN_COMPONENT Error: image_morph failed");
}

