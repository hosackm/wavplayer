#pragma once

#include <stdlib.h>  // size_t

#define WAV_HEADER_SIZE (44)

// header described in: http://soundfile.sapp.org/doc/WaveFormat/
typedef struct wav_header {
    char  ChunkID[4];     // "RIFF"
    int   ChunkSize;
    char  Format[4];      // "WAVE"
    char  Subchunk1ID[4]; // "fmt 
    int   Subchunk1Size;  // 16 if PCM
    short AudioFormat;    // PCM = 1, IEE Float = 3, 
    short NumChannels;
    int   SampleRate;
    int   ByteRate;       // nchans * samplerate * bytes-per-sample
    short BlockAlign;     // nchans * bytes-per-sample
    short BitsPerSample;
    char  Subchunk2ID[4]; // "data"
    int   Subchunk2Size;  // num bytes from here to EOF
} wav_header_s;

void print_header(wav_header_s *hdr);
size_t wav_header_size();
