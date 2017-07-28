wavplayer
=========

Simple wav file player using [libsndfile](http://www.mega-nerd.com/libsndfile) and [portaudio](http://www.portaudio.com).  The wavplayer will
take a wav file on the command line, open it with libsndfile and on every
callback from portaudio read NUM_FRAMES_PER_BUFFER for the left and right
channels, and output them on the portaudio stream.  

### To Compile

The wavplayer makes use of libsndfile and libportaudio so these two 
libraries will need to be linked during the build process.  For Example:
```
clang main.c -o wavplayer -lsndfile -lportaudio -L/PATH/TO/LIBSNDFILE -L/PATH/TO/PORTAUDIO
```

### To Run

A wav file shall be passed through the command line.  For example:
```
./wavplayer /PATH/TO/YOUR/WAV/FILE/filename.wav
```

### To Do / Requests

* Playlist for opening multiple files
* UI for opening files and play / pause
* Buffering for samples instead of reading with sf_read_float() in real-time
* Equalization filters
* Other formats
