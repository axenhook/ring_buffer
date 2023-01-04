
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ring_buffer.h"

#define min(a,b) (((a) < (b)) ?  (a) : (b))

ring_buffer_t *ring_buffer_init(unsigned int size)
{
    ring_buffer_t *rb;

    /* size must be a power of 2 */
    assert(!(size & (size - 1)));

    rb = malloc(sizeof(ring_buffer_t));
    if (!rb) 
    {
        return NULL;
    }

    rb->buffer = malloc(size);
    if (!rb->buffer)
    {
        free(rb);
        return NULL;
    }

    rb->size = size;
    rb->in = rb->out = 0;

    return rb;
}

void ring_buffer_destroy(ring_buffer_t *rb)
{
    assert(rb != NULL);

    free(rb->buffer);
    free(rb);
}

unsigned int ring_buffer_put(ring_buffer_t *rb, unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    len = min(len, rb->size - rb->in + rb->out);

    /* first put the data starting from rb->in to buffer end */
    l = min(len, rb->size - (rb->in & (rb->size - 1)));
    memcpy(rb->buffer + (rb->in & (rb->size - 1)), buffer, l);

    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(rb->buffer, buffer + l, len - l);

    rb->in += len;

    return len;
}

unsigned int ring_buffer_get(ring_buffer_t *rb, unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    len = min(len, rb->in - rb->out);

    /* first get the data from rb->out until the end of the buffer */
    l = min(len, rb->size - (rb->out & (rb->size - 1)));
    memcpy(buffer, rb->buffer + (rb->out & (rb->size - 1)), l);

    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, rb->buffer, len - l);

    rb->out += len;

    return len;
}

