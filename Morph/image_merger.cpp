#include "image_merger.h"

image_merger::image_merger(std::string file_addr)
    try : img_pro(file_addr) {
        if (file_addr.empty()) {
            std::cout << stderr << "Empty Str Received" << std::endl;
            throw "IMAGE_MERGER Error, Received empty string as file path";
        }
        if (file_addr[file_addr.size() - 1] != '/') {
            file_addr += '/';
        }
        path = file_addr;
        res_img = 0;
    } catch (std::string err_log) {
        throw err_log;
    }

image_merger::~image_merger() {}

bool image_merger::merg_image(std::string img_name) {
    if (img_name.empty()) {
        std::cout << stderr << "IMAGE_MERGER Error, Received empty string as file path" << std::endl;
        execute_error_hint("IMAGE_MERGER Error", "Received empty string as file path");
        return false;
    }

    IplImage *r_channel,
             *g_channel,
             *b_channel;

    try {
        r_channel = img_pro.load_image_as_object(path + "r.bw");
        g_channel = img_pro.load_image_as_object(path + "g.bw");
        b_channel = img_pro.load_image_as_object(path + "b.bw");
    } catch (std::string err_log) {
        execute_error_hint("IMAGE_MERGER Catch", err_log);
        return false;
    }

    res_img = img_pro.init_image(cvGetSize(r_channel), IPL_DEPTH_8U, 3);

    img_pro.gene_image(r_channel, g_channel, b_channel, res_img);

    img_pro.save_image(img_name, res_img);

    return true;
}

IplImage* image_merger::get_merged_image() {
    if (res_img) {
        return res_img;
    }
    return (IplImage *)0;
}

void image_merger::execute_error_hint(std::string text, std::string informative_text, std::string detailed_text) {
    QMessageBox msg_box;
    msg_box.setText(QString(text.c_str()));
    msg_box.setInformativeText(QString(informative_text.c_str()));
    if (!detailed_text.empty())
        msg_box.setDetailedText(QString(detailed_text.c_str()));
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.setDefaultButton(QMessageBox::Ok);

    int ret = msg_box.exec();
    switch (ret) {
    case QMessageBox::Ok:
        std::cout << "Ok" << std::endl;;
        break;
    default:
        assert("Unexpected Button Type");
        break;
    }
}

void image_merger::__check_path__() {
    std::cout << stderr << "Path: " << path << std::endl;
    exit(9);
}

