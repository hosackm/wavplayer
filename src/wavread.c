#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wavhdr.h"

int main(int argc, char *argv[])
{
    int bytes_read;
    char buf[256];
    FILE *fp = NULL;
    wav_header_s hdr;
    const size_t header_size = wav_header_size();

    fp = fopen("output.wav", "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "Couldn't open output.wav\n");
        return 1;
    }

    bytes_read = fread(buf, 1, header_size, fp);
    if(bytes_read < header_size)
    {
        fprintf(stderr, "Read %d bytes instead of %lu\n", bytes_read, header_size);
        return 2;
    }

    memcpy(&hdr, buf, sizeof(wav_header_s));

    print_header(&hdr);

    return 0;
}
