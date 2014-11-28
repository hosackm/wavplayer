wavplayer
=========

Simple wav file player using libsndfile and portaudio.  The wavplayer will
take a wav file on the command line, open it with libsndfile and on every
callback from portaudio read NUM_FRAMES_PER_BUFFER for the left and right
channels, and output them on the portaudio stream.  

###To Compile

The wavplayer makes use of libsndfile and libportaudio so these two 
libraries will need to be linked during the build process.  For Example:
```
clang main.c -o wavplayer -lsndfile -lportaudio -L/PATH/TO/LIBSNDFILE -L/PATH/TO/PORTAUDIO
```

###To Run

A wav file shall be passed through the command line.  For example:
```
./wavplayer /PATH/TO/YOUR/WAV/FILE/filename.wav
```

###Limitations
*The wav file is stereo
*The file must be in wav format
*The wavplayer will play only one file and then exit
