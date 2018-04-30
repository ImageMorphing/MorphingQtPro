#ifndef IMAGE_IO_PROCESSOR_H
#define IMAGE_IO_PROCESSOR_H

#include <iostream>
#include <cassert>

#include <cv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <QMessageBox>

class image_io_processor {
public:
    image_io_processor(std::string);
    ~image_io_processor();

    // file I/O related
    bool save_image_as_object(std::string img_name, const cv::Mat mat);
    bool save_image_as_object(std::string img_name, const IplImage* img);
    IplImage* load_image_as_object(std::string img_name);

    bool save_image(std::string img_name, cv::Mat mat);
    bool save_image(std::string img_name, IplImage *img);

    IplImage* load_image(std::string img_name);

    // image created related
    IplImage* init_image(CvSize size, int depth, int channels);

    // image check related
    bool show_image(IplImage *img, std::string img_name = "");

    // image generate related
    IplImage* gene_image(IplImage* r, IplImage *g, IplImage *b, IplImage *res_img = 0);

    // image convert related
    bool conv_image(IplImage* img, char** img_ptr, int index = -1);

private:
    std::string path;

    // image generate related
    IplImage* gene_image_by_3x3(IplImage *r_channel, IplImage *g_channel, IplImage *b_channel, IplImage *res_img = 0);
    IplImage* gene_image_by_3x1(IplImage *r_plane, IplImage *g_plane, IplImage *b_plane, IplImage *res_img = 0);

    void execute_error_hint(std::string text, std::string informative_text, std::string detailed_text = "");
};


#endif // IMAGE_IO_PROCESSOR_H
