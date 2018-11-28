cmake_minimum_required(VERSION 3.1)
project(VideoMerger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

set(src_dir "src")
set(include_dir "include")
set(bin_dir "bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})
include_directories(${include_dir})
include_directories(${Boost_INCLUDE_DIR})
aux_source_directory(${src_dir} srcs)

add_executable("main" ${srcs})
target_link_libraries("main" ${OpenCV_LIBS})
target_link_libraries("main" ${Boost_LIBRARIES})