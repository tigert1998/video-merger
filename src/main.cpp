#include <iostream>
#include <opencv2/videoio.hpp>

#include "types.h"

using std::cout;
using cv::VideoCapture;

int main(int argc, char **argv) {
    for (u32 i = 0; i < argc; i++)
        cout << argv[i] << "\n";
    VideoCapture capturer();
    return 0;
}