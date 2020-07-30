#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdio>


int main(int argc, char** argv) {
    cv::namedWindow("Example4", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Log_Polar", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap(argv[1]);

    double fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << "FPS: " << fps << std::endl;

    cv::Size size(
        (int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)
    );
    std::cout << "Size: " << size << std::endl;

    cv::VideoWriter writer;
    writer.open(argv[2], writer.fourcc('M', 'J', 'P', 'G'), fps, size);

    cv::Mat logpolar_frame, bgr_frame;

    for (;;) {
        cap >> bgr_frame;
        if (bgr_frame.empty()) break;
        cv::imshow("Example4", bgr_frame);

        cv::logPolar(
            bgr_frame,
            logpolar_frame,
            cv::Point2f(
                bgr_frame.cols/2,
                bgr_frame.rows/2
            ),
            40,
            cv::WARP_FILL_OUTLIERS
        );

        cv::imshow("Log_Polar", logpolar_frame);
        writer << logpolar_frame;

        char c = cv::waitKey(10);
        if (c == 27) break;
    }

    cap.release();

    return 0;
}
