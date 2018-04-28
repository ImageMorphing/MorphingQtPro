#ifndef IMAGE_IO_PROCESSOR_H
#define IMAGE_IO_PROCESSOR_H

#include <iostream>

#include <cv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

class image_io_processor {
public:
    image_io_processor(std::string);
    ~image_io_processor();

    // file I/O related
    void save_image_as_object(std::string img_name, const cv::Mat mat);
    void save_image_as_object(std::string img_name, const IplImage* img);
    IplImage* load_image_as_object(std::string img_name);

    void save_image(std::string img_name, cv::Mat mat);
    void save_image(std::string img_name, IplImage *img);

    IplImage* load_image(std::string img_name);

    // image created related
    IplImage* init_image(CvSize size, int depth, int channels);

    // image check related
    void show_image(IplImage *img, std::string img_name = "");

    // image generate related
    IplImage* gene_image(IplImage* r, IplImage *g, IplImage *b, IplImage *res_img = 0);

    // image convert related
    void conv_image(IplImage* img, char** img_ptr, int index = -1);

private:
    // image generate related
    IplImage* gene_image_by_3x3(IplImage *r_channel, IplImage *g_channel, IplImage *b_channel, IplImage *res_img = 0);
    IplImage* gene_image_by_3x1(IplImage *r_plane, IplImage *g_plane, IplImage *b_plane, IplImage *res_img = 0);

    std::string path;
};


#endif // IMAGE_IO_PROCESSOR_H
