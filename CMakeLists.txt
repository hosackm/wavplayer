cmake_minimum_required(VERSION 3.0)
project(wavtools)

set(ENABLE_EXTERNAL_LIBS OFF CACHE BOOL "No flac, opus, or vorbis for libsndfile")
set(PA_USE_JACK OFF CACHE BOOL "Don't use JACK with portaudio")

add_subdirectory(vendor/libsndfile)
add_subdirectory(vendor/portaudio)

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
target_link_libraries(wavwrite PortAudio)
target_include_directories(wavwrite PUBLIC vendor/portaudio/include)

# add and configure wavplay target
# needs portaudio
add_executable(wavplay src/wavplay.c src/wavhdr.c)
target_link_libraries(wavplay sndfile)
target_include_directories(wavplay PUBLIC sndfile)
target_include_directories(wavplay PUBLIC src)
target_link_libraries(wavplay PortAudio)
target_include_directories(wavplay PUBLIC vendor/portaudio/include)
