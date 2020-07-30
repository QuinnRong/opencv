#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>


int main(int argc, char** argv) {
    cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;

    if (argc == 1) {
        cap.open(0);
    } else {
        cap.open(argv[1]);
    }

    if (!cap.isOpened()) {
        std::cerr << "Couldn't open capture." << std::endl;
    } else {
        cv::Mat frame;
        int count = 0;
        for (;;) {
            cap >> frame;
            if (frame.empty()) break;
            cv::imshow("Example2", frame);
            std::cout << ++count << std::endl;
            if (cv::waitKey(33) >= 0) break;
        }
    }
 
    cv::destroyWindow("Example3");

    return 0;
}
