#include "image_util.h"

image_util::image_util(std::string file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Received Empty String" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty string as file path");
    }
    path = file_addr;
    if (file_addr[file_addr.size() - 1] != '/') {
        path += '/';
    }
}

image_util::~image_util() {}

image_ptr image_util::read_image_as_bw(IplImage *img) {
    auto img_ptr = tran_image(img);
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty pointer");
        return image_ptr(0);
    }
    if (img->nChannels != 1) {
        std::cout << stderr << "Unexpected Dimension Received" << std::endl;
        std::stringstream strstream;
        strstream << img->nChannels;
        throw std::string("IMAGE_UTIL Error, Received unexpected dimension: " + strstream.str());
        return image_ptr(0);
    }
    memcpy(img_ptr->ch[0], img->imageData, img_ptr->height * img_ptr->width);
    return img_ptr;
}

image_ptr image_util::read_mesh(std::string file_name) {
    /*
     * This function is used to read mesh files
     */
    auto file_path = path + file_name;
    FILE* fin = 0;
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty string as file path");
        return image_ptr(0);
    }
    if ((fin = fopen(file_path.data(), "r")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        throw std::string("IMAGE_UTIL Error, Reading file failed: " + file_path);
        return image_ptr(0);
    }
    auto img_ptr = tran_image(fin);
    fread(img_ptr->ch[0], img_ptr->width * img_ptr->height, 2 * sizeof(float), fin);
    fclose(fin);
    return img_ptr;
}

void image_util::save_image_as_bw(image_ptr img, std::string file_name) {
    FILE* fout = 0;
    std::string file_path = path + file_name;
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty pointer");
    }
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty string as file path");
    }
    if ((fout = fopen(file_path.data(), "w")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        throw std::string("IMAGE_UTIL Error, Reading file failed: " + file_path);
    }
    fwrite(&img->width, sizeof(int), 1, fout);
    fwrite(&img->height, sizeof(int), 1, fout);
    fwrite(img->ch[0], img->width * img->height, 1, fout);
    fclose(fout);
}

void image_util::save_mesh(image_ptr mes, std::string file_name) {
    FILE* fout = 0;
    std::string file_path = path + file_name;
    if (mes == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty pointer");
    }
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        throw std::string("IMAGE_UTIL Error, Received empty string as file path");
    }
    if ((fout = fopen(file_path.data(), "w")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        throw std::string("IMAGE_UTIL Error, Reading file failed: " + file_path);
    }
    fwrite(&mes->width, sizeof(int), 1, fout);
    fwrite(&mes->height, sizeof(int), 1, fout);
    fwrite(mes->ch[0], mes->width * mes->height, 2 * sizeof(float), fout);
    fclose(fout);
}

image_ptr image_util::allo_image(int width, int height, int type) {
    image_ptr ptr = new image_struct();
    if (ptr == 0) {
        std::cout << stderr << "Cannot allocate memory" << std::endl;
        throw std::string("IMAGE_UTIL Error, Allocate memory failed");
        return image_ptr(0);
    }
    ptr->width = width;
    ptr->height = height;

    switch (type) {
        case BW:
            ptr->ch[0] = (uchar *)malloc(width * height);
            break;
        case MESH:
            ptr->ch[0] = (float *)malloc(2 * width * height * sizeof(float));
            ptr->ch[1] = (float *)ptr->ch[0] + width * height;
            break;
        default:
            std::cout << stderr << "Unexpected type" << std::endl;
            exit(1);
            break;
    }
    return ptr;
}

void image_util::free_image(image_ptr ptr) {
    free((char *) ptr->ch[0]);
    free(ptr);
}

image_ptr image_util::tran_image(IplImage *img) {
    image_ptr ptr = new image_struct();
    if (ptr == 0) {
        std::cout << stderr << "Cannot allocate memory" << std::endl;
        throw std::string("IMAGE_UTIL Error, Allocate memory failed");
        return image_ptr(0);
    }
    ptr->height = img->height;
    ptr->width = img->width;
    ptr->ch[0] = (uchar *) malloc (ptr->height * ptr->width);
    return ptr;
}

image_ptr image_util::tran_image(FILE* fin) {
    image_ptr ptr = new image_struct();
    if (ptr == 0) {
        std::cout << stderr << "Cannot allocate memory" << std::endl;
        throw std::string("IMAGE_UTIL Error, Allocate memory failed");
        return image_ptr(0);
    }
    fread(&ptr->width, sizeof(int), 1, fin);
    fread(&ptr->height, sizeof(int), 1, fin);
    ptr->ch[0] = (float *) malloc (2 * ptr->width * ptr->height * sizeof(float));
    ptr->ch[1] = (float *) ptr->ch[0] + ptr->height * ptr->width;
    return ptr;
}

void image_util::execute_error_hint(std::string text, std::string informative_text, std::string detailed_text) {
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
