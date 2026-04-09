#include <stdint.h>

struct wav_header{
    char riff[4];
    int32_t flength;
    char wave[4];
    char fmt[4];
    int32_t chunk_size;
    int16_t format_tag;
    int16_t num_chains;
    int32_t srate;
    int32_t bytes_per_sec;
    int16_t bytes_per_samp;
    int16_t bits_per_samp;
    char data[4];
    int32_t dlength;
};

typedef struct wav_data_array{
    int16_t *data;
    uint32_t nr;
}wav_data_array;

void write_to_wav(struct wav_data_array *array);

void read_wav_data(const char *filename, wav_data_array *input_data);
