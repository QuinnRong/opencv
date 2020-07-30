#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


void img2txt(cv::Mat &img, const std::string &txt) {
    std::ofstream fout(txt);

    int B, G, R;
    for (int r = 0; r < img.rows; ++r) {
        for (int c = 0; c < img.cols; ++c) {
            B = img.at<cv::Vec3b>(r, c)[0];
            G = img.at<cv::Vec3b>(r, c)[1];
            R = img.at<cv::Vec3b>(r, c)[2];
            // std::cout << "[" << r << "," << c << "] "
            //           << "{" << B << "," << G << "," << R << "}" << std::endl;
            fout << B << std::endl;
            fout << G << std::endl;
            fout << R << std::endl;
        }
    }

    fout.close();
}

void resize(const cv::Mat &img, const std::string &name, const std::string &out,
            const cv::Size &size, const int type) {
    cv::Mat resized;
    cv::resize(img, resized, size, type);
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, resized);
    img2txt(resized, out);
}

int main(int argc, char **argv) {
    cv::Mat data = cv::imread("../lena.jpeg");
    std::cout << "size: " << data.size << std::endl;
    std::cout << "rows: " << data.rows << std::endl;
    std::cout << "cols: " << data.cols << std::endl;
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("img", data);

    resize(data, "near", "../near.txt", cv::Size(70, 100), cv::INTER_NEAREST);

    resize(data, "linear", "../linear.txt", cv::Size(70, 100), cv::INTER_LINEAR);

    cv::waitKey(0);

    return 0;
}