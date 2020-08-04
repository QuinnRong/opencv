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
    cv::resize(img, resized, size, 0, 0, type);
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, resized);
    // img2txt(resized, out);
}

void lena() {
    cv::Mat data = cv::imread("../lena.jpeg");
    std::cout << "size: " << data.size << std::endl;
    std::cout << "rows: " << data.rows << std::endl;
    std::cout << "cols: " << data.cols << std::endl;
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("img", data);

    resize(data, "near", "../near.txt", cv::Size(1920, 1680), cv::INTER_NEAREST);
    resize(data, "linear", "../linear.txt", cv::Size(1920, 1680), cv::INTER_LINEAR);

    cv::waitKey(0);
}

void resize_yuv() {
    int width = 1920, height = 1080;
    int width_resized = 1080, height_resized = 720;

    std::ifstream ifs;
    ifs.open("../1920_1080_p420.yuv", std::ios::in | std::ios::binary);
    int filesize = height * width * 3 / 2;
    char *input = new char[filesize];
    ifs.read(input, filesize);
    ifs.close();
    cv::Mat data(height + height / 2, width, CV_8UC1, input);

    cv::namedWindow("data", cv::WINDOW_AUTOSIZE);
    cv::imshow("data", data);

    // ### method 1
    cv::Mat rgb;
    cvtColor(data, rgb, cv::COLOR_YUV2RGB_NV12);
    std::cout << rgb.rows << " x " << rgb.cols << std::endl;
    cv::namedWindow("rgb", cv::WINDOW_AUTOSIZE);
    cv::imshow("rgb", rgb);
    cv::Mat resized;
    cv::resize(rgb, resized, cv::Size(width_resized, height_resized), 0, 0, cv::INTER_LINEAR);
    std::cout << resized.rows << " x " << resized.cols << std::endl;
    cv::namedWindow("method1", cv::WINDOW_AUTOSIZE);
    cv::imshow("method1", resized);

    // ### method 2
    unsigned char *data_y = new unsigned char[width * height];
    memcpy(data_y, data.data, width * height);
    cv::Mat part_y(height, width, CV_8UC1, data_y);

    unsigned char *data_uv = new unsigned char[height / 2 * width];
    memcpy(data_uv, data.data + height * width, height / 2 * width);
    cv::Mat part_uv(height / 2, width / 2, CV_8UC2, data_uv);

    cv::Mat resized_y;
    cv::resize(part_y, resized_y, cv::Size(width_resized, height_resized), 0, 0, cv::INTER_LINEAR);
    std::cout << resized_y.rows << " x " << resized_y.cols << std::endl;

    cv::Mat resized_uv;
    cv::resize(part_uv, resized_uv, cv::Size(width_resized / 2, height_resized / 2), 0, 0, cv::INTER_LINEAR);
    std::cout << resized_uv.rows << " x " << resized_uv.cols << std::endl;

    unsigned char *data_yuv = new unsigned char[(height_resized + height_resized / 2) * width_resized];
    memcpy(data_yuv, resized_y.data, height_resized * width_resized);
    memcpy(data_yuv + height_resized * width_resized, resized_uv.data, height_resized / 2 * width_resized);
    cv::Mat resized_final(height_resized + height_resized / 2, width_resized, CV_8UC1, data_yuv);
    cv::Mat rgb_final;
    cvtColor(resized_final, rgb_final, cv::COLOR_YUV2RGB_NV12);
    std::cout << rgb_final.rows << " x " << rgb_final.cols << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << int(rgb_final.data[i]) << std::endl;
    }
    cv::namedWindow("method2", cv::WINDOW_AUTOSIZE);
    cv::imshow("method2", rgb_final);

    cv::waitKey(0);

    delete[] data_y;
    delete[] data_uv;
    delete[] data_yuv;
    delete[] input;
}

int main(int argc, char **argv) {
    // lena();

    resize_yuv();

    return 0;
}
