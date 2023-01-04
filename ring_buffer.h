
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ring_buffer {
 unsigned char *buffer; /* the buffer holding the data */
 unsigned int size; /* the size of the allocated buffer */
 unsigned int in; /* data is added at offset (in % size) */
 unsigned int out; /* data is extracted from off. (out % size) */
} ring_buffer_t;

ring_buffer_t *ring_buffer_init(unsigned int size);
void ring_buffer_destroy(ring_buffer_t *rb);
unsigned int ring_buffer_put(ring_buffer_t *rb, unsigned char *buffer, unsigned int len);
unsigned int ring_buffer_get(ring_buffer_t *rb, unsigned char *buffer, unsigned int len);

static inline unsigned int ring_buffer_len(ring_buffer_t *rb)
{
 return rb->in - rb->out;
}

#ifdef __cplusplus
}
#endif

#endif
