#include <stdio.h>
#include <string.h>
#include "wav_process.h"


struct wav_header header;

const int sample_rate = 48000;
const int duration = 10;
const int header_length = sizeof(header);

void write_to_wav(wav_data_array *audio_data){
    strncpy(header.riff, "RIFF", 4);
    strncpy(header.wave, "WAVE", 4);
    strncpy(header.data, "data", 4);
    strncpy(header.fmt, "fmt ", 4);

    header.chunk_size = 16;
    header.format_tag = 1;
    header.num_chains = 1;
    header.srate = sample_rate;
    header.bits_per_samp = 16;
    header.bytes_per_sec = header.srate * header.bits_per_samp / 8 * header.num_chains;
    header.bytes_per_samp = header.bits_per_samp / 8 * header.num_chains;
    
    int buffer_size = audio_data->nr;
    header.dlength = buffer_size * 2;
    header.flength = header.dlength + header_length;
    FILE *fp = fopen("output.wav", "wb");
    fwrite(&header, 1, header_length, fp);
    fwrite(audio_data->data, 2, buffer_size, fp);
    fclose(fp);

}

void read_wav_data(const char *filename, wav_data_array *input_data){
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 44, SEEK_SET);
    input_data->nr = (filesize - 44) / 2;
    fread(input_data->data, 2, input_data->nr, fp);
    fclose(fp);
}