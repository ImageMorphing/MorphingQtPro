#include "main_component.h"


main_component::main_component(std::string file_addr, std::string base_name, unsigned int frame_num)
    try :img_pro(file_addr), img_utl(file_addr), img_sep(file_addr) {
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

main_component::main_component(std::string base_name, unsigned int frame_num) {
    this->frame_num = frame_num;
    this->frame_base_name = base_name;
}

IplImage* main_component::execute_by_morph(std::string scr_image_name,
                                           std::string tgt_image_name,
                                           unsigned int mesh_width,
                                           unsigned int mesh_height,
                                           float *cor_x1,
                                           float *cor_y1,
                                           float *cor_x2,
                                           float *cor_y2) {
    IplImage* scr_img = img_pro.load_image(scr_image_name),
            * tgt_img = img_pro.load_image(tgt_image_name);

    img_sep.sepe_image(scr_image_name);
    img_sep.sepe_image(tgt_image_name);

    IplImage *tgt_img_R = img_pro.load_image_as_object(tgt_image_name + "_r.obj");

    image_ptr M1 = img_utl.allo_image(mesh_width, mesh_height, MESH),
              M2 = img_utl.allo_image(mesh_width, mesh_height, MESH);

//    for (int i = 0; i < mesh_width * mesh_height; ++ i) {
//        corX1[i] = (i % 4) * mesh_width / 3.;
//        corY1[i] = (i / 4) * mesh_height / 3.;
//        corX2[i] = (i % 4) * mesh_width / 3.;
//        corY2[i] = (i / 4) * mesh_height / 3.;
//    }

    std::cout << std::endl;

//    corX2[9] = 200;
//    corY2[9] = 300;
    M1->ch[0] = cor_x1;
    M1->ch[1] = cor_y1;
    M2->ch[0] = cor_x2;
    M2->ch[1] = cor_y2;

    IplImage* R_Pl_S = img_pro.init_image(cvGetSize(tgt_img_R), IPL_DEPTH_8U, 1),
            * G_Pl_S = cvCloneImage(R_Pl_S),
            * B_Pl_S = cvCloneImage(R_Pl_S),
            * R_Pl_T = cvCloneImage(R_Pl_S),
            * G_Pl_T = cvCloneImage(R_Pl_S),
            * B_Pl_T = cvCloneImage(R_Pl_S);

    cvSplit(scr_img, B_Pl_S, G_Pl_S, R_Pl_S, NULL);
    cvSplit(tgt_img, B_Pl_T, G_Pl_T, R_Pl_T, NULL);
    image_meshwarp(R_Pl_S, M1, M2, R_Pl_T);
    image_meshwarp(G_Pl_S, M1, M2, G_Pl_T);
    image_meshwarp(B_Pl_S, M1, M2, B_Pl_T);
    tgt_img = cvCreateImage(cvGetSize(scr_img), IPL_DEPTH_8U, 3);
    cvZero(tgt_img);
    cvMerge(B_Pl_T, G_Pl_T, R_Pl_T, NULL, tgt_img);
    return tgt_img;
}

