#pragma once

#include <vector>
#include <string>
#include <functional>

#include <opencv2/opencv.hpp>

class VideoMerger {
public:
    static VideoMerger shared;

    void Synthesize(
        std::vector<std::string> picture_paths, 
        std::string video_path, 
        std::string output_video_path,
        std::string watermark_text,
        std::function<void(double)> progress) const;

private:
    static void AddWatermark(cv::Mat &mat, std::string text);
    static cv::Mat CoverLeft(const cv::Mat &a, const cv::Mat &b, double progress);
};