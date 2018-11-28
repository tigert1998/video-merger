#pragma once

#include <vector>
#include <string>

class VideoMerger {
public:
    static VideoMerger shared;

    void Synthesize(
        std::vector<std::string> picture_paths, 
        std::string video_path, 
        std::string output_video_path) const;
private:
    
};