#include "image_portrait_processor.h"

image_portrait_processor::image_portrait_processor(std::string file_addr):img_pro(file_addr) {
    if (file_addr.empty()) {
        std::cerr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if (file_addr[file_addr.size() - 1] != '/') {
        file_addr += '/';
    }
    path = file_addr;
}

void image_portrait_processor::execute(std::string src_img_name, std::string tgt_img_name, std::string dat_name, unsigned int epoch, bool is_delaunay_visible = false, bool is_points_visible = false) {

    if (src_img_name.empty() || tgt_img_name.empty() || dat_name.empty()) {
        throw std::string("BAD_ARGUMENT");
    }

    cv::Mat src_img = cv::Mat(cv::cvarrToMat(img_pro.load_image(src_img_name)));
    cv::Mat tgt_img = cv::Mat(cv::cvarrToMat(img_pro.load_image(tgt_img_name)));

    cv::Rect rect = cv::Rect(0, 0, src_img.size().width, src_img.size().height);

    src_img.convertTo(src_img, CV_32F);
    tgt_img.convertTo(tgt_img, CV_32F);

    cv::Mat img_morph = cv::Mat::zeros(src_img.size(), CV_32FC3);

    auto src_fod = face_detection(dat_name, src_img_name);
    auto tgt_fod = face_detection(dat_name, tgt_img_name);

    auto src_points = generate_point2f_vector(src_fod);
    auto tgt_points = generate_point2f_vector(tgt_fod);
    generate_outside_points2f_vector(src_points, rect);
    generate_outside_points2f_vector(tgt_points, rect);
    std::vector<cv::Point2f> points;

    for (double alpha = 1. / epoch; alpha <= 1.01; alpha += 1. / epoch) {
        std::cout << alpha << std::endl;
        points.clear();
        for (int i = 0; i < src_points.size(); i++) {
            float x, y;
            x = ( 1 - alpha ) * src_points[i].x + alpha * tgt_points[i].x;
            y = ( 1 - alpha ) * src_points[i].y + alpha * tgt_points[i].y;

            points.push_back(cv::Point2f(x, y));

            if (is_points_visible) {
                cv::Scalar color(255, 0, 255);
                draw_point(src_img, cv::Point2f(x, y), color);
                draw_point(tgt_img, cv::Point2f(x, y), color);
            }
        }

        cv::Subdiv2D subdiv(rect);
        subdiv.insert(points);
        auto res_vec = generate_delaunay_pointes_vector(subdiv, rect, points);

        if (is_delaunay_visible) {
            cv::Scalar color(255, 0, 0);
            draw_delaunay(src_img, subdiv, color);
            draw_delaunay(tgt_img, subdiv, color);
        }

        for (int i = 0; i < res_vec.size(); i++) {
            auto index_vec = res_vec[i];
            std::vector<cv::Point2f> t1, t2, t;

            t1.push_back( src_points[index_vec[0]] );
            t1.push_back( src_points[index_vec[1]] );
            t1.push_back( src_points[index_vec[2]] );

            t2.push_back( tgt_points[index_vec[0]] );
            t2.push_back( tgt_points[index_vec[1]] );
            t2.push_back( tgt_points[index_vec[2]] );

            t.push_back( points[index_vec[0]] );
            t.push_back( points[index_vec[1]] );
            t.push_back( points[index_vec[2]] );

            morph_triangle(src_img, tgt_img, img_morph, t1, t2, t, alpha);
        }


        cv::imshow("Morphed Face", img_morph / 255.0);
        cv::waitKey(0);
    }
}

void image_portrait_processor::draw_delaunay(cv::Mat& img, cv::Subdiv2D& subdiv, cv::Scalar delaunay_color) {
    std::vector<cv::Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    std::vector<cv::Point> pt(3);
    cv::Size size = img.size();
    cv::Rect rect(0,0, size.width, size.height);

    for (size_t i = 0; i < triangleList.size(); i++) {
        cv::Vec6f t = triangleList[i];
        pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));

        // Draw rectangles completely inside the image.
        if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])) {
            cv::line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
            cv::line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
            cv::line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
        }
    }
}

void image_portrait_processor::draw_point(cv::Mat& img, cv::Point2f fp, cv::Scalar color) {
    circle(img, fp, 2, color, CV_FILLED, CV_AA, 0 );
}

dlib::full_object_detection image_portrait_processor::face_detection(std::string dat_name, std::string img_name) {
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    dlib::shape_predictor pose_model;
    dlib::deserialize(path + dat_name) >> pose_model;
    cv::Mat mt = cv::imread(path + img_name);

    dlib::array2d<unsigned char> img;
    load_image(img, path + img_name);
    dlib::cv_image<dlib::bgr_pixel> cimg(mt);
    std::vector<dlib::rectangle> faces = detector(cimg);
    std::vector<dlib::full_object_detection> shapes;
    for (unsigned long i = 0; i < faces.size(); ++i)
        shapes.push_back(pose_model(cimg, faces[i]));

    if (!shapes.empty()) {
        return shapes[0];
    } else {
        throw std::string("No face detected!");
    }
}

std::vector<cv::Point2f> image_portrait_processor::generate_point2f_vector(dlib::full_object_detection fod) {
    std::vector<cv::Point2f> vec;
    for (int i = 0; i < 68; i++) {
        vec.push_back(cv::Point2f(fod.part(i).x(), fod.part(i).y()));
    }
    return vec;
}

std::vector<cv::Point2f> image_portrait_processor::generate_outside_points2f_vector(std::vector<cv::Point2f>& vec, cv::Rect& rect) {
    using namespace cv;
    auto width = rect.width;
    auto height = rect.height;
    vec.push_back(Point2f(0, 0));
    vec.push_back(Point2f(0, height / 3));
    vec.push_back(Point2f(0, height / 3 * 2));
    vec.push_back(Point2f(0, height - 1));

    vec.push_back(Point2f(width / 3, height / 3));
    vec.push_back(Point2f(width / 3 * 2, height / 3));

    vec.push_back(Point2f(width - 1, height / 5));
    vec.push_back(Point2f(width / 4 * 3, height / 5));
    vec.push_back(Point2f(width / 4 * 2, height / 5));
    vec.push_back(Point2f(width / 4 * 1, height / 5));
    vec.push_back(Point2f(width / 4 * 0, height / 5));

    vec.push_back(Point2f(width - 1, height / 10 * 3));
    vec.push_back(Point2f(width / 4 * 3, height / 10 * 3));
    vec.push_back(Point2f(width / 4 * 2, height / 10 * 3));
    vec.push_back(Point2f(width / 4 * 1, height / 10 * 3));
    vec.push_back(Point2f(width / 4 * 0, height / 10 * 3));

    vec.push_back(Point2f(width / 2, 0));
    vec.push_back(Point2f(width / 3, height - 1));
    vec.push_back(Point2f(width / 3 * 2, height - 1));
    vec.push_back(Point2f(width - 1, 0));
    vec.push_back(Point2f(width - 1, height / 3));
    vec.push_back(Point2f(width - 1, height / 3 * 2));
    vec.push_back(Point2f(width - 1, height - 1));
    return vec;
}

std::vector<std::vector<int>> image_portrait_processor::generate_delaunay_pointes_vector(
                                                    cv::Subdiv2D& subdiv,
                                                    const cv::Rect& rect,
                                                    const std::vector<cv::Point2f>& points) {
    std::vector<cv::Vec6f> triangle_list;
    subdiv.getTriangleList(triangle_list);

    std::vector<cv::Point2f> pt(3);
    std::vector<int> ind(3);
    std::vector<std::vector<int>> delaunay_triangles;
    for (size_t i = 0; i < triangle_list.size(); ++i) {
        cv::Vec6f t = triangle_list[i];
        pt[0] = cv::Point2f(t[0], t[1]);
        pt[1] = cv::Point2f(t[2], t[3]);
        pt[2] = cv::Point2f(t[4], t[5]);

        if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])) {
            int count = 0;
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < points.size(); k++) {
                    if (abs(pt[j].x - points[k].x) < 1.0 && abs(pt[j].y - points[k].y) < 1.0) {
                        ind[j] = k;
                        count++;
                    }
                }
            }
            if (count == 3) {
                delaunay_triangles.push_back(ind);
            }
        }
    }
    return delaunay_triangles;
}

void image_portrait_processor::apply_affine_transform(cv::Mat &warpImage, cv::Mat &src, std::vector<cv::Point2f> &srcTri, std::vector<cv::Point2f> &dstTri) {

    cv::Mat warpMat = getAffineTransform( srcTri, dstTri );

    cv::warpAffine( src, warpImage, warpMat, warpImage.size(), cv::INTER_LINEAR, cv::BORDER_REFLECT_101);
}

void image_portrait_processor::morph_triangle(cv::Mat &img1, cv::Mat &img2, cv::Mat &img, std::vector<cv::Point2f> &t1, std::vector<cv::Point2f> &t2, std::vector<cv::Point2f> &t, double alpha) {

    using namespace cv;

    // Find bounding rectangle for each triangle
    Rect r = boundingRect(t);
    Rect r1 = boundingRect(t1);
    Rect r2 = boundingRect(t2);

    // Offset points by left top corner of the respective rectangles
    std::vector<Point2f> t1Rect, t2Rect, tRect;
    std::vector<Point> tRectInt;
    for(int i = 0; i < 3; i++) {
        tRect.push_back( Point2f( t[i].x - r.x, t[i].y -  r.y) );
        tRectInt.push_back( Point(t[i].x - r.x, t[i].y - r.y) ); // for fillConvexPoly

        t1Rect.push_back( Point2f( t1[i].x - r1.x, t1[i].y -  r1.y) );
        t2Rect.push_back( Point2f( t2[i].x - r2.x, t2[i].y - r2.y) );
    }

    // Get mask by filling triangle
    Mat mask = Mat::zeros(r.height, r.width, CV_32FC3);
    fillConvexPoly(mask, tRectInt, Scalar(1.0, 1.0, 1.0), 16, 0);

    // Apply warpImage to small rectangular patches
    Mat img1Rect, img2Rect;
    img1(r1).copyTo(img1Rect);
    img2(r2).copyTo(img2Rect);

    Mat warpImage1 = Mat::zeros(r.height, r.width, img1Rect.type());
    Mat warpImage2 = Mat::zeros(r.height, r.width, img2Rect.type());

    apply_affine_transform(warpImage1, img1Rect, t1Rect, tRect);
    apply_affine_transform(warpImage2, img2Rect, t2Rect, tRect);

    // Alpha blend rectangular patches
    Mat imgRect = (1.0 - alpha) * warpImage1 + alpha * warpImage2;

    // Copy triangular region of the rectangular patch to the output image
    multiply(imgRect, mask, imgRect);
    multiply(img(r), Scalar(1.0,1.0,1.0) - mask, img(r));
    img(r) = img(r) + imgRect;
}

void image_portrait_processor::execute_error_hint(std::string text, std::string informative_text, std::string detailed_text) {
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
