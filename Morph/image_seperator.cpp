#include "image_seperator.h"

image_seperator::image_seperator(std::string file_addr): img_pro(file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        throw "IMAGE_SEPERATOR Error", "Received empty string as file path";
    }
    if (file_addr[file_addr.size() - 1] != '/') {
        file_addr += '/';
    }
    path = file_addr;
}

image_seperator::~image_seperator() {

}

void image_seperator::sepe_image(std::string img_name) {
    IplImage *src_img = img_pro.load_image(img_name),
             *r_plane = img_pro.init_image(cvGetSize(src_img), IPL_DEPTH_8U, 1),
             *g_plane = cvCloneImage(r_plane),
             *b_plane = cvCloneImage(r_plane);

    cvSplit(src_img, b_plane, g_plane, r_plane, NULL);

    // Begin to write output files
    // output the red channel jpg file
    img_pro.save_image_as_object(img_name + "_r.obj", r_plane);

    // output the green channel BW file
    img_pro.save_image_as_object(img_name + "_g.obj", g_plane);

    // output the blue channel BW file
    img_pro.save_image_as_object(img_name + "_b.obj", b_plane);
}

void image_seperator::execute_error_hint(std::string text, std::string informative_text, std::string detailed_text) {
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

void image_seperator::__check_path__() {
    std::cout << stderr << "Path: " << path << std::endl;
    exit(9);
}

