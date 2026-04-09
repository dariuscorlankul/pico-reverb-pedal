#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ring_buffers.h"
#include "wav_process.h"

#define SAMPLE_RATE 48000
#define SCALING_FACTOR 48
#define BUFFERSIZE_SMALL 2048
#define BUFFERSIZE_MEDIUM 4096
#define MAX_SAMPLE 480000
#define BUFFERSIZE_LARGE 8192

//init arrays and buffers
int32_t reflection_buffer_array[BUFFERSIZE_SMALL];
ring_buffer_32 reflection_buffer;

int16_t input_array[]
//early reflection timing array
uint16_t reflection_timing[10] = {2, 3, 5, 10, 12, 18, 21, 26, 29, 35};

void init_arrays(uint16_t *reflection_timing){
   for(int i = 0; i < 10; i++ ){
    reflection_timing[i] = reflection_timing[i] * SCALING_FACTOR;
   } 
    ring32_init(&reflection_buffer, reflection_buffer_array, BUFFERSIZE_SMALL);
}

void process_early_reflections(ring_buffer_32 *reflection_buffer, int32_t incoming_data, uint16_t pre_delay, uint16_t *reflection_timing){
    for(int i = 0; i < 10; i++){
        ring32_write_delayed(&reflection_buffer, incoming_data,  (pre_delay + reflection_timing[i]));
    }
}

void proccess_diffusions();

int main(){
    init_arrays(&reflection_timing);
    read_wav_data("data.wav", )
    return 0;
}
