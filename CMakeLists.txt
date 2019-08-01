cmake_minimum_required(VERSION 3.12)
project(neon)

set(CMAKE_CXX_STANDARD 17)

add_executable(neon src/main.cpp src/imagegen.cpp src/imagegen.h src/httputil.h src/httputil.cpp)

target_link_libraries(neon fmt)
include_directories(httplib)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(neon Threads::Threads)

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(neon ${ImageMagick_LIBRARIES})
