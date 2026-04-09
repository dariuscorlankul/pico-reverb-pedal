#include <stdint.h>
#include "ring_buffers.h"

void ring32_init(ring_buffer_32 *dl, int32_t *memory_array, uint32_t size){
    dl->data = memory_array;
    dl->mask = size - 1;
    dl->write_index = 0;

    for(uint32_t i = 0; i < size; i++){
        dl->data[i] = 0;
    }
}

void ring32_write(ring_buffer_32 *dl, int32_t incoming_data){
    dl->data[dl->write_index] = incoming_data;

    dl->write_index = (dl->write_index + 1) & dl->mask;

}

void ring32_write_delayed(ring_buffer_32 *dl, int32_t incoming_data, uint16_t delay){
    dl->data[(dl->write_index - delay) & dl->mask] = incoming_data;

    dl->write_index = (dl->write_index + 1) & dl->mask;
}

int32_t ring32_read(ring_buffer_32 *dl, int32_t delay_in_samples){
    uint32_t read_index = (dl->write_index - delay_in_samples) & dl->mask;
    return dl->data[read_index];
}


void ring16_init(ring_buffer_16 *dl, int16_t *memory_array, uint16_t size){
    dl->data = memory_array;
    dl->mask = size - 1;
    dl->write_index = 0;

    for(uint16_t i = 0; i < size; i++){
        dl->data[i] = 0;
    }
}

void ring16_write(ring_buffer_16 *dl, int16_t incoming_data){
    dl->data[dl->write_index] = incoming_data;

    dl->write_index = (dl->write_index + 1) & dl->mask;

}

void ring16_write_delayed(ring_buffer_16 *dl, int16_t incoming_data, uint16_t delay){
    dl->data[(dl->write_index - delay) & dl->mask] = incoming_data;
    dl->write_index = (dl->write_index + 1) & dl->mask;
}

int16_t ring16_read(ring_buffer_16 *dl, int16_t delay_in_samples){
    uint16_t read_index = (dl->write_index - delay_in_samples) & dl->mask;
    return dl->data[read_index];
}