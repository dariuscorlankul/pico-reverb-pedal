#pragma once
#include <stdint.h>

typedef struct ring_buffer_32{
    int32_t* data;
    uint16_t mask;
    uint16_t write_index;
} ring_buffer_32;

void ring32_init(ring_buffer_32 *dl, int32_t *memory_array, uint32_t size);

void ring32_write(ring_buffer_32 *dl, int32_t incoming_data);

void ring32_write_delayed(ring_buffer_32 *dl, int32_t incoming_data, uint16_t write_delay);

int32_t ring32_read(ring_buffer_32 *dl, int32_t delay_in_samples);

typedef struct ring_buffer_16{
    int16_t* data;
    uint16_t mask;
    uint16_t write_index;
} ring_buffer_16;

void ring16_init(ring_buffer_16 *dl, int16_t *memory_array, uint16_t size);

void ring16_write(ring_buffer_16 *dl, int16_t incoming_data);

void ring16_write_delayed(ring_buffer_16 *dl, int16_t incoming_data, uint16_t write_delay);

int16_t ring16_read(ring_buffer_16 *dl, int16_t delay_in_samples);