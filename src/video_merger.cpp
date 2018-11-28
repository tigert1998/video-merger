#include "video_merger.h"
#include "bad_file_access.h"
#include "constants.h"
#include "types.h"

#include <opencv2/opencv.hpp>

using cv::VideoWriter, cv::VideoCapture, cv::Mat, cv::Size, cv::Point, cv::Scalar;
using std::string, std::vector, std::function;

VideoMerger VideoMerger::shared;

void VideoMerger::Synthesize(
    vector<string> picture_paths,
    string video_path,
    string output_video_path,
    std::string watermark_text,
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
        AddWatermark(pictures[i], watermark_text);
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
        AddWatermark(mat, watermark_text);
        writer << mat;
        progress(static_cast<double>(pictures.size() + i + 1) / (frame_count + pictures.size()));
    }
}

void VideoMerger::AddWatermark(cv::Mat &mat, std::string text) {
    Scalar white = Scalar::all(255);
    Scalar black = Scalar::all(0);

    int font_face = cv::FONT_HERSHEY_SCRIPT_SIMPLEX, thickness = 1, base_line;
    double font_scale = 1.2;

    Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &base_line);
    base_line += thickness;
    cv::Point origin(0, mat.rows - base_line);
    
    rectangle(mat, origin + Point(0, base_line),
        origin + Point(text_size.width, -text_size.height),
        black, cv::FILLED);

    cv::putText(mat, text, origin, font_face, font_scale, white, thickness);
}