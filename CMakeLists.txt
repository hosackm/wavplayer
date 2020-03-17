cmake_minimum_required(VERSION 3.0)
project(wavtools)

add_executable(wavwrite src/wavwrite.c)
add_executable(wavread src/wavread.c)
add_executable(wavplay src/wavplay.c)

# find_package(portaudio)
# 'portaudio_static' target
