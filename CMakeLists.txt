cmake_minimum_required(VERSION 3.0)
project(wavtools)

add_subdirectory(extern/libsndfile)
add_subdirectory(extern/portaudio)

# add and configure wavread target
add_executable(wavread src/wavread.c src/wavhdr.c)
target_link_libraries(wavread sndfile)
target_include_directories(wavread PUBLIC sndfile)
target_include_directories(wavread PUBLIC src)

# add and configure wavwrite target
# needs portaudio
add_executable(wavwrite src/wavwrite.c src/wavhdr.c)
target_link_libraries(wavwrite sndfile)
target_include_directories(wavwrite PUBLIC sndfile)
target_include_directories(wavwrite PUBLIC src)
target_link_libraries(wavwrite portaudio_static)
target_include_directories(wavwrite PUBLIC portaudio)

# add and configure wavplay target
# needs portaudio
add_executable(wavplay src/wavplay.c src/wavhdr.c)
target_link_libraries(wavplay sndfile)
target_include_directories(wavplay PUBLIC sndfile)
target_include_directories(wavplay PUBLIC src)
target_link_libraries(wavplay portaudio_static)
target_include_directories(wavplay PUBLIC portaudio)
