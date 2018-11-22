#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "portaudio.h"

#define SAMPLE_RATE             (48000)
#define NUM_SAMPLES_PER_FRAME   (512)
#define NUM_CHANNELS            (1)

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

int callback
    (const void                         *input
    ,void                               *output,
    unsigned long frameCount
    ,const PaStreamCallbackTimeInfo     *timeInfo
    ,PaStreamCallbackFlags               statusFlags
    ,void                               *userData
    )
{
    int *p_in = (int*)input;
    FILE *fp = (FILE*)userData;
    unsigned long i;

    fwrite(p_in, sizeof(int), frameCount * NUM_CHANNELS, fp);

    return paContinue;
}

void write_wav_header(FILE *fp);

void usage();

int main(int argc, char * argv[])
{
    int num_seconds;
    PaStream *p_stream;
    PaError error;
    FILE *p_outfile;

    if(argc < 2)
    {
        usage();
        return 0;
    }

    p_outfile = fopen("output.wav", "wb");
    if(p_outfile == NULL)
    {
        fprintf(stderr, "Unable to open output.wav\n");
        return 1;
    }

    fseek(p_outfile, sizeof(wav_header_s), SEEK_SET);

    num_seconds = atoi(argv[1]);

    error = Pa_Initialize();
    if(error != paNoError)
    {
        return 1;
    }

    error = Pa_OpenDefaultStream
        (&p_stream
        ,NUM_CHANNELS
        ,0
        ,paInt32
        ,SAMPLE_RATE
        ,NUM_SAMPLES_PER_FRAME
        ,callback
        ,p_outfile
        );
    if(error != paNoError)
    {
        fprintf(stderr, "Error: %s\n", Pa_GetErrorText(error));
        return 2;
    }

    error = Pa_StartStream(p_stream);
    if(error != paNoError)
    {
        return 3;
    }

    Pa_Sleep(1000 * num_seconds);

    Pa_StopStream(p_stream);
    Pa_CloseStream(p_stream);
    Pa_Terminate();

    // close WAV FILE
    write_wav_header(p_outfile);
    fclose(p_outfile);

    return 0;
}

void usage()
{
    fprintf(stdout, "usage: wavwrite [NUM_SECONDS]\n");
}

void write_wav_header(FILE *fp)
{
    int filesize;
    wav_header_s header;

    // get filesize then rewind to beginning
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    // filesize minus the WAV header
    header.Subchunk2Size = filesize - 44;

    // ChunkID[4];     // "RIFF"
    header.ChunkID[0] = 'R';
    header.ChunkID[1] = 'I';
    header.ChunkID[2] = 'F';
    header.ChunkID[3] = 'F';

    // ChunkSize;
    header.ChunkSize = 36 + header.Subchunk2Size;

    // Format[4];      // "WAVE"
    header.Format[0] = 'W';
    header.Format[1] = 'A';
    header.Format[2] = 'V';
    header.Format[3] = 'E';

    // Subchunk1ID[4]; // "fmt 
    header.Subchunk1ID[0] = 'f';
    header.Subchunk1ID[1] = 'm';
    header.Subchunk1ID[2] = 't';
    header.Subchunk1ID[3] = ' ';

    // Subchunk1Size;  // 16 if PCM
    header.Subchunk1Size = 16;

    // AudioFormat;    // PCM = 1 
    header.AudioFormat = 1;

    // NumChannels;
    header.NumChannels = 1;

    // SampleRate;
    header.SampleRate = 48000;

    // ByteRate;       // nchans * samplerate * bytes-per-sample
    header.ByteRate = 48000 * 1 * sizeof(int);

    // BlockAlign;     // nchans * bytes-per-sample
    header.BlockAlign = 1 * sizeof(int);

    // BitsPerSample;
    header.BitsPerSample = sizeof(int) * 8;

    // Subchunk2ID;    // "data"
    header.Subchunk2ID[0] = 'd';
    header.Subchunk2ID[1] = 'a';
    header.Subchunk2ID[2] = 't';
    header.Subchunk2ID[3] = 'a';

    // Subchunk2Size;  // num bytes from here to EOF
    header.Subchunk2Size = 0;

    fwrite(&header, sizeof(wav_header_s), 1, fp);
}
