#include <stdio.h>
#include <string.h>
#include "wavhdr.h"

void print_header(wav_header_s *hdr)
{
    char buf[5] = "\0\0\0\0\0";

    if(!hdr)
        return;

    // Copy strings to null terminated buffer before printing
    memcpy(buf, hdr->ChunkID, sizeof(hdr->ChunkID));
    fprintf(stdout, "ChunkID:      '%s'\n", buf);

    fprintf(stdout, "ChunkSize:     %d bytes\n", hdr->ChunkSize);

    memcpy(buf, hdr->Format, sizeof(hdr->Format));
    fprintf(stdout, "Format:       '%s'\n", buf);

    memcpy(buf, hdr->Subchunk1ID, sizeof(hdr->Subchunk1ID));
    fprintf(stdout, "Subchunk1ID:  '%s'\n", buf);

    fprintf(stdout, "Subchunk1Size: %d\n", hdr->Subchunk1Size);
    fprintf(stdout, "AudioFormat:   %d\n", hdr->AudioFormat);
    fprintf(stdout, "Num Channels:  %d\n", hdr->NumChannels);
    fprintf(stdout, "SampleRate:    %d Hz\n", hdr->SampleRate);
    fprintf(stdout, "ByteRate:      %d bytes/sec\n", hdr->ByteRate);
    fprintf(stdout, "BlockAlign:    %d bytes\n", hdr->BlockAlign);
    fprintf(stdout, "BitsPerSample: %d bits\n", hdr->BitsPerSample);
    fprintf(stdout, "NumChannels:   %d\n", hdr->NumChannels);

    memcpy(buf, hdr->Subchunk2ID, sizeof(hdr->Subchunk2ID));
    fprintf(stdout, "Subchunk2ID:  '%s'\n", buf);

    fprintf(stdout, "Subchunk2Size: %d bytes\n", hdr->Subchunk2Size);
}

size_t wav_header_size()
{
    return sizeof(wav_header_s);
}
