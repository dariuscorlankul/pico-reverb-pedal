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

int16_t input_array[MAX_SAMPLE];
wav_data_array input_data;
//early reflection timing array
uint16_t reflection_timing[10] = {5, 7, 9, 10, 15, 18, 21, 26, 29, 35};

void init_arrays(uint16_t *reflection_timing){
   for(int i = 0; i < 10; i++ ){
    reflection_timing[i] = reflection_timing[i] * SCALING_FACTOR;
   } 
    ring32_init(&reflection_buffer, reflection_buffer_array, BUFFERSIZE_SMALL);
}

void process_early_reflections(ring_buffer_32 *reflection_buffer, int32_t incoming_data, uint16_t pre_delay, uint16_t *reflection_timing){
    int32_t incoming_q16 = incoming_data * 65536;
    for(int i = 0; i < 10; i++){
        ring32_write_delayed(reflection_buffer, incoming_q16,  (pre_delay + reflection_timing[i]));
    }
    //ring32_write_delayed(reflection_buffer, incoming_q16, reflection_timing[9]);    
}

void proccess_diffusions();

int main(){
    int16_t output_array[MAX_SAMPLE] = {};
    wav_data_array output_data;
    output_data.data = output_array;
    output_data.nr = 0;

    init_arrays(reflection_timing);
    input_data.data = input_array;
    read_wav_data("data.wav", &input_data);
    
    // Process input through early reflections
    for(uint32_t i = 0; i < input_data.nr && output_data.nr < MAX_SAMPLE; i++){
        process_early_reflections(&reflection_buffer, input_data.data[i], 0, reflection_timing);
        
        int64_t output = 0;
        
        // Mix in early reflections
        for(int j = 0; j < 10; j++){
            output += ring32_read(&reflection_buffer, reflection_timing[j]);
        }
        
        // Average reflections and scale from Q16.16 to int16
        output /= 4;
        output_data.data[output_data.nr] = (int16_t)(output >> 16);
        output_data.nr++;
    }
    
    // Continue reading reflections after input ends (tail of the reverb)
    uint16_t max_delay = reflection_timing[9];
    for(uint16_t i = 0; i < max_delay && output_data.nr < MAX_SAMPLE; i++){
        process_early_reflections(&reflection_buffer, 0, 0, reflection_timing);

        int64_t output = 0;
        
        // Mix in early reflections
        for(int j = 0; j < 10; j++){
            output += ring32_read(&reflection_buffer, reflection_timing[j]);
        }
        
        // Average reflections and scale from Q16.16 to int16
        output /= 10;
        output_data.data[output_data.nr] = (int16_t)(output >> 16);
        output_data.nr++;
    }
    
    write_to_wav(&output_data);
    return 0;
}
