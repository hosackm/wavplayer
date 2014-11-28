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

#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (512)
#define NUM_CHANNELS        (2)

typedef struct
{
    SNDFILE *s;
    unsigned int eof;
    float buffer[FRAMES_PER_BUFFER * NUM_CHANNELS];
} data_s;

static int callback(    const void *input, void *output,
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData );

int main(int argc, const char * argv[])
{
    /* SNDFILE variables */
    SF_INFO info;
    SNDFILE *s;
    FILE *f;
    
    /* PortAudio variables */
    data_s data;
    PaStream *stream;
    PaError error;
/***************************************************************
************************* INIT SNDFILE *************************
***************************************************************/
    info.channels = NUM_CHANNELS;
    info.samplerate = SAMPLE_RATE;
    info.format = SF_FORMAT_WAV;
    
    if(argc < 2)
    {
        printf("Must pass command line argument\n");
        return 0;
    }
    
    if(sf_format_check(&info) < 0)
    {
        printf("Error with your sf_info structure\n");
        return -1;
    }
    
    s = sf_open(argv[1], SFM_READ, &info);
    
    if (sf_error(s) != SF_ERR_NO_ERROR)
    {
        printf("%s\n",sf_strerror(s));
        printf("File: %s\n", argv[1]);
        return -1;
    }

/***************************************************************
************************* INIT PORTAUDIO ***********************
****************************************************************/
    data.s = s;
    data.eof = 0;
    
    error = Pa_Initialize();
    if(error != paNoError)
    {
        printf("Problem initializing\n");
    }
    
    error = Pa_OpenDefaultStream(&stream
                                 ,0                     /* no input */
                                 ,NUM_CHANNELS          /* stereo out */
                                 ,paFloat32             /* floating point */
                                 ,44100.
                                 ,FRAMES_PER_BUFFER
                                 ,callback
                                 ,(void*)&data);        /* our sndfile data struct */
    if(error != paNoError)
    {
        printf("Problem opening Default Stream\n");
    }
    
    error = Pa_StartStream(stream);
    if(error != paNoError)
    {
        printf("Problem opening starting Stream\n");
    }
/***************************************************************
************************ SLEEP / PROCESS ***********************
***************************************************************/
    while(!data.eof)
    {
        Pa_Sleep(100);
    }
/***************************************************************
*************************** CLOSE UP ***************************
***************************************************************/
    error = Pa_CloseStream(stream);
    if(error != paNoError)
    {
        printf("Problem closing stream\n");
    }
    
    error = Pa_Terminate();
    if(error != paNoError)
    {
        printf("Problem terminating\n");
    }
    
    fclose(f);
    sf_close(s);
    
    return 0;
}

static int callback(    const void *input
                        ,void *output
                        ,unsigned long frameCount
                        ,const PaStreamCallbackTimeInfo* timeInfo
                        ,PaStreamCallbackFlags statusFlags
                        ,void *userData )
{
    unsigned int i;
    sf_count_t num_read;
    float *out = (float*)output;
    data_s *data = (data_s*)userData;
    
    num_read = sf_read_float(data->s, &data->buffer[0], frameCount * NUM_CHANNELS);
    /* Write the samples we read from the file */
    for(i = 0; i < num_read; ++i)
    {
        *out++ = data->buffer[2 * i];
        *out++ = data->buffer[2 * i + 1];
    }
    
    /*  We've reached the end of the file since we
    *   couldn't read as many samples as we wanted to
    */
    if (num_read < frameCount) {
        for(i = 0; i < frameCount - num_read; ++i)
        {
            *out++ = 0.0f;
            *out++ = 0.0f;
        }
        data->eof = 1;
    }
    
    /* Clear out the buffer for the next time around */
    memset(data->buffer, 0.0, sizeof(float) * 2 * FRAMES_PER_BUFFER);
    
    return paNoError;
}
