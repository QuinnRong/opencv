#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>

// 视频对象
cv::VideoCapture g_cap;

// 表示要播放的帧数，（>1：连续模式，1：单步模式，0：等待，<0：连续模式）
// 初始状态下或手动调整进度条后，需要[置1]以刷新窗口
int g_run = 1;
// 用来保证在连续模式下，调整进度条不会进入单步模式
int g_dontset = 0;

// 手动调整进度条时，会更新该值，表示调整后的位置
int g_slider_position = 0;

// 手动调整进度条时，会触发该回调函数
void onTrackbarSlide(int pos, void *) {
    // 改变播放进度
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    // 连续模式下不[置1]
    if (!g_dontset) {
        // [置1]，以刷新窗口
        g_run = 1;
    }
    std::cout << "Slide, run = " << g_run << std::endl;
}

int main(int argc, char** argv) {
    cv::namedWindow("Example2-2", cv::WINDOW_AUTOSIZE);

    // 打开视频
    g_cap.open(argv[1]);
    int frames = g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw   = g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph   = g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    printf("Video has %d frames of dimension(%d, %d).\n", frames, tmpw, tmph);

    // 增加进度条
    cv::createTrackbar("Position", "Example2-2", &g_slider_position, frames, 
                        onTrackbarSlide);

    // 播放
    cv::Mat frame;
    for (;;) {
        // 刷新窗口
        if (g_run != 0) {
            // 窗口会刷新，不需要[置1]
            g_dontset = 1;

            g_cap >> frame;
            if (frame.empty()) break;

            int current_pos = g_cap.get(cv::CAP_PROP_POS_FRAMES);
            cv::setTrackbarPos("Position", "Example2-2", current_pos);
            cv::imshow("Example2-2", frame);

            g_run -= 1;
        } else {
            // 窗口不会刷新，需要[置1]
            g_dontset = 0;
        }

        // 处理键盘输入
        char c = cv::waitKey(33);
        // 单步模式
        if (c == 's') {
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        }
        // 连续模式
        if (c == 'r') {
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }
        // Esc键表示退出
        if (c == 27) {
            break;
        }
    }

    cv::destroyWindow("Example2-2");

    return 0;
}
