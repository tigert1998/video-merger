#include <iostream>
#include <string>
#include <iomanip>
#include <boost/program_options.hpp>

#include "constants.h"
#include "types.h"
#include "video_merger.h"

using std::cout, std::cerr, std::string, std::vector;

vector<string> picture_paths;
string video_path, output_path, watermark_text;

void Init(int argc, char **argv) {
    using namespace boost::program_options;
    options_description desc;
    desc.add_options()
        ("help", "Help screen.")
        ("video_path", value<string>(), 
            "The path of input video.")
        ("picture_paths", value<vector<string>>()->multitoken(), 
            "The paths of pictures.")
        ("output_path", value<string>()->default_value("output.avi"), 
            "The output video path.")
        ("watermark_text", value<string>()->default_value(author_name), 
            "A line of text which will be placed on the bottom of video. Default value is author's name.");

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        if (vm.count("help")) {
            cout << desc;
            exit(1);
        }
        if (!vm.count("video_path") || !vm.count("picture_paths")) {
            cout << "Not sufficient arguments!\n" << desc;
            exit(1);
        }
    
        video_path = vm["video_path"].as<string>();
        output_path = vm["output_path"].as<string>();
        watermark_text = vm["watermark_text"].as<string>();
        picture_paths = vm["picture_paths"].as<vector<string>>();
        cout << "video_path = \"" << video_path << "\"\n";
        cout << "output_path = \"" << output_path << "\"\n";
        cout << "watermark_text = \"" << watermark_text << "\"\n";
        for (u32 i = 0; i < picture_paths.size(); i++) {
            cout << "picture_paths[" << i << "] = \"" << picture_paths[i] << "\"\n";
        }
    } catch (...) {
        cout << "Incorrect argument format!\n" << desc;
        exit(1);
    }
}

int main(int argc, char **argv) {
    Init(argc, argv);
    VideoMerger::shared.Synthesize(
        picture_paths, video_path, output_path, watermark_text, [] (double progress) {
        cout << "\rGenerating progress: " 
            << std::fixed << std::setprecision(2) << (progress * 100) << "%";
    });
    cout << "\n";
    return 0;
}