#include "video_merger.h"
#include "bad_file_access.h"
#include "constants.h"
#include "types.h"

#include <opencv2/opencv.hpp>

using cv::VideoWriter, cv::VideoCapture, cv::Mat, cv::Size;
using std::string, std::vector, std::function;

VideoMerger VideoMerger::shared;

void VideoMerger::Synthesize(
    vector<string> picture_paths,
    string video_path,
    string output_video_path,
    function<void(double)> progress) const {
    
    VideoCapture capturer;
    capturer.open(video_path);
    if (!capturer.isOpened())
        throw BadFileAccess("Video at \"" + video_path + "\" is badly formatted");
    
    u32 width = capturer.get(CV_CAP_PROP_FRAME_WIDTH);
    u32 height = capturer.get(CV_CAP_PROP_FRAME_HEIGHT);
    u32 fps = capturer.get(CV_CAP_PROP_FPS);
    u32 frame_count = capturer.get(CV_CAP_PROP_FRAME_COUNT);

    Size output_size = Size(width, height);

    vector<Mat> pictures(picture_paths.size());
    for (u32 i = 0; i < pictures.size(); i++) {
        auto path = picture_paths[i];
        pictures[i] = cv::imread(path);
        if (!pictures[i].data)
            throw BadFileAccess("Picture at \"" + path + "\" is badly formatted");
        cv::resize(pictures[i], pictures[i], output_size);
        progress(static_cast<double>(i + 1) / (frame_count + pictures.size()));
    }

    VideoWriter writer;

    writer.open(
        output_video_path,
        VideoWriter::fourcc('D', 'I', 'V', 'X'), 
        fps, output_size);

    for (u32 i = 0; i < pictures.size(); i++) {
        for (u32 j = 0; j < (1000 / fps); j++)
            writer << pictures[i];    
    }
    for (u32 i = 0; i < frame_count; i++) {
        Mat mat;
        capturer >> mat;
        writer << mat;
        progress(static_cast<double>(pictures.size() + i + 1) / (frame_count + pictures.size()));
    }
}