#ifndef IMAGE_PORTRAIT_PROCESSOR_H
#define IMAGE_PORTRAIT_PROCESSOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <vector>

#include "image_io_processor.h"

class image_portrait_processor {
public:
    image_portrait_processor(std::string file_addr);

    void execute(std::string src_img, std::string tgt_img, std::string dat_name, unsigned int epoch, bool is_delaunay_visible, bool is_points_visible);

private:
    std::string path;

    image_io_processor img_pro;

    void draw_delaunay(cv::Mat& img, cv::Subdiv2D& subdiv, cv::Scalar delaunay_color);

    void draw_point(cv::Mat& img, cv::Point2f fp, cv::Scalar color);

    dlib::full_object_detection face_detection(std::string dat_name, std::string img_name);

    std::vector<cv::Point2f> generate_point2f_vector(dlib::full_object_detection fod);

    std::vector<cv::Point2f> generate_outside_points2f_vector(std::vector<cv::Point2f>& vec, cv::Rect& rect);

    std::vector<std::vector<int>> generate_delaunay_pointes_vector(cv::Subdiv2D& subdiv, const cv::Rect& rect, const std::vector<cv::Point2f>& points);

    void apply_affine_transform(cv::Mat &warpImage, cv::Mat &src, std::vector<cv::Point2f> &srcTri, std::vector<cv::Point2f> &dstTri);

    void morph_triangle(cv::Mat &img1, cv::Mat &img2, cv::Mat &img, std::vector<cv::Point2f> &t1, std::vector<cv::Point2f> &t2, std::vector<cv::Point2f> &t, double alpha);

    void execute_error_hint(std::string, std::string, std::string detailed_text = "");
};


#endif // IMAGE_PORTRAIT_PROCESSOR_H
