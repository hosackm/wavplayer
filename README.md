wavtools
========

Simple wav tools that make use of [libsndfile](http://www.mega-nerd.com/libsndfile) and [portaudio](http://www.portaudio.com) to read, write, and play wav files through a soundcard.  This repository is mostly to acquiant myself with libsndfile and WAV files.

### To Build

These tools make use of the 3rd party libsndfile.  Make sure to get the source for this submodule using the following:

    git submodule update --init --recursive

Then you can build the project using cmake. Run the following:

    mkdir build && cd build
    cmake ..
    make
