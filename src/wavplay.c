//
//  main.c
//  sndfile_tutorial
//
//  Created by Matthew Hosack on 11/28/14.
//  Copyright (c) 2014 Matthew Hosack. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "sndfile.h"
#include "portaudio.h"

#define FRAMES_PER_BUFFER   (512)

typedef struct
{
    SNDFILE     *file;
    SF_INFO      info;
} callback_data_s;

static int callback(    const void *input, void *output,
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData );

int main(int argc, const char * argv[])
{
    SNDFILE *file;
    PaStream *stream;
    PaError error;
    callback_data_s data;

    /* Check cli arguments */
    if(argc < 2)
    {
        fprintf(stderr, "Must pass file to play\n");
        return 1;
    }
        
    /* Open the soundfile */
    data.file = sf_open(argv[1], SFM_READ, &data.info);
    if (sf_error(data.file) != SF_ERR_NO_ERROR)
    {
        fprintf(stderr, "%s\n", sf_strerror(data.file));
        fprintf(stderr, "File: %s\n", argv[1]);
        return 1;
    }
    
    /* init portaudio */
    error = Pa_Initialize();
    if(error != paNoError)
    {
        fprintf(stderr, "Problem initializing\n");
        return 1;
    }
    
    /* Open PaStream with values read from the file */
    error = Pa_OpenDefaultStream(&stream
                                 ,0                     /* no input */
                                 ,data.info.channels         /* stereo out */
                                 ,paFloat32             /* floating point */
                                 ,data.info.samplerate
                                 ,FRAMES_PER_BUFFER
                                 ,callback
                                 ,&data);        /* our sndfile data struct */
    if(error != paNoError)
    {
        fprintf(stderr, "Problem opening Default Stream\n");
        return 1;
    }
    
    /* Start the stream */
    error = Pa_StartStream(stream);
    if(error != paNoError)
    {
        fprintf(stderr, "Problem opening starting Stream\n");
        return 1;
    }

    /* Run until EOF is reached */
    while(Pa_IsStreamActive(stream))
    {
        Pa_Sleep(100);
    }

    /* Close the soundfile */
    sf_close(data.file);

    /*  Shut down portaudio */
    error = Pa_CloseStream(stream);
    if(error != paNoError)
    {
        fprintf(stderr, "Problem closing stream\n");
        return 1;
    }
    
    error = Pa_Terminate();
    if(error != paNoError)
    {
        fprintf(stderr, "Problem terminating\n");
        return 1;
    }
    
    return 0;
}

static
int
callback
    (const void                     *input
    ,void                           *output
    ,unsigned long                   frameCount
    ,const PaStreamCallbackTimeInfo *timeInfo
    ,PaStreamCallbackFlags           statusFlags
    ,void                           *userData
    )
{
    float           *out;
    callback_data_s *p_data = (callback_data_s*)userData;
    sf_count_t       num_read;

    out = (float*)output;
    p_data = (callback_data_s*)userData;

    /* clear output buffer */
    memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

    /* read directly into output buffer */
    num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);
    
    /*  If we couldn't read a full frameCount of samples we've reached EOF */
    if (num_read < frameCount)
    {
        return paComplete;
    }
    
    return paContinue;
}
