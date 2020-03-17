cmake_minimum_required(VERSION 3.0)
project(wavtools)

add_subdirectory(extern/libsndfile)
add_subdirectory(extern/portaudio)

# add and configure wavwrite target
add_executable(wavwrite src/wavwrite.c)
target_link_libraries(wavwrite portaudio_static)
# target_link_libraries(wavwrite sndfile)
target_include_directories(wavwrite PUBLIC extern/portaudio/include)
# target_include_directories(wavwrite PUBLIC extern/portaudio/src/common)
# target_include_directories(wavwrite PUBLIC sndfile)

# add and configure wavread target
# add_executable(wavread src/wavread.c)
# target_link_libraries(wavread portaudio_static)
# target_link_libraries(wavread sndfile)
# target_include_directories(wavread PUBLIC extern/portaudio/include)
# target_include_directories(wavread PUBLIC sndfile)

# add and configure wavplay target
# add_executable(wavplay src/wavplay.c)
# target_link_libraries(wavplay portaudio_static)
# target_link_libraries(wavplay sndfile)
# target_include_directories(wavplay PUBLIC extern/portaudio/include)
# target_include_directories(wavplay PUBLIC sndfile)
