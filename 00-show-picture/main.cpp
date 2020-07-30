#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1], -1);
    if (img.empty()) {
       std::cout << "Empty image: " << argv[1] << std::endl;
       return -1;
    }

    cv::namedWindow("Example1-in", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-in", img);
    cv::waitKey(0);

    cv::Mat out;
    cv::GaussianBlur(img, out, cv::Size(5,5), 3, 3);
    cv::namedWindow("Example1-Gaussian", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-Gaussian", out);
    cv::waitKey(0);

    cv::pyrDown(img, out);
    cv::namedWindow("Example1-pyrDown", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-pyrDown", out);
    cv::waitKey(0);

    cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
    cv::namedWindow("Example1-Gray", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-Gray", out);
    cv::waitKey(0);

    cv::Canny(img, out, 10, 100, 3, true);
    cv::namedWindow("Example1-Canny", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-Canny", out);
    cv::waitKey(0);

    cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
    cv::pyrDown(out, out);
    cv::pyrDown(out, out);
    cv::Canny(out, out, 10, 100, 3, true);
    cv::namedWindow("Example1-Serial", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1-Serial", out);
    cv::waitKey(0);

    return 0;
}
