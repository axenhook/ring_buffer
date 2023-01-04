#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "../ring_buffer.h"

#define RING_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    ring_buffer_t *rb;
    int member = 0;

    rb = ring_buffer_init(RING_BUFFER_SIZE);
    assert(rb != NULL);
    
    for (int i = 0; i < RING_BUFFER_SIZE / 4; i++)
    {
        member = i;
        assert(ring_buffer_put(rb, (unsigned char *)&member, 4) == 4);
    }

    assert(ring_buffer_len(rb) == RING_BUFFER_SIZE);
    assert(ring_buffer_put(rb, (unsigned char *)&member, 4) == 0);
    assert(ring_buffer_len(rb) == RING_BUFFER_SIZE);
    
    for (int i = 0; i < RING_BUFFER_SIZE / 4; i++)
    {
        assert(ring_buffer_get(rb, (unsigned char *)&member, 4) == 4);
        assert(member == i);
    }

    assert(ring_buffer_len(rb) == 0);
    assert(ring_buffer_get(rb, (unsigned char *)&member, 4) == 0);
    assert(ring_buffer_len(rb) == 0);

    ring_buffer_destroy(rb);
    
    return 0;
}

