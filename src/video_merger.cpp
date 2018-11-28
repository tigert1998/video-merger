#include "video_merger.h"
#include "bad_file_access.h"
#include "constants.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using cv::VideoWriter, cv::VideoCapture;

VideoMerger VideoMerger::shared;

void VideoMerger::Synthesize(
    std::vector<std::string> picture_paths,
    std::string video_path,
    std::string output_video_path) const {
    
    VideoCapture capturer;
    capturer.open(video_path);
    if (!capturer.isOpened())
        throw BadFileAccess("Video at " + video_path + " is badly formatted");
    
    double width = capturer.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = capturer.get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = capturer.get(CV_CAP_PROP_FPS);

    LOG_EXPR(width);
    LOG_EXPR(height);
    LOG_EXPR(fps);

    VideoWriter writer;
    
    // writer.open(output_video_path, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, );
}