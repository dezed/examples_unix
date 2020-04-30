#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "mac/circular_buffer.h"

#if 1
/*https://github.com/embeddedartistry/embedded-resources/blob/master/examples/c/circular_buffer/circular_buffer.c)*/

// The definition of our circular buffer structure is hidden from the user
struct circular_buf_t {
	void* buffer;
	size_t max;
	size_t el_size;
	bool full;

	size_t head_idx;
	size_t tail_idx;
};


static void advance_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	if(cbuf->full)
	{
		cbuf->tail_idx = (cbuf->tail_idx + 1) % cbuf->max;
	}

	cbuf->head_idx = (cbuf->head_idx + 1) % cbuf->max;

	// We mark full because we will advance tail on the next time around
	cbuf->full = (cbuf->head_idx == cbuf->tail_idx);
}

static void retreat_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail_idx = (cbuf->tail_idx +1 ) % cbuf->max;
}


cbuf_handle_t circular_buf_init( void* buffer, size_t el_size, size_t size)
{
	assert(buffer && size);

	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
	assert(cbuf);

	cbuf->buffer = buffer;
	cbuf->max = size;
	cbuf->el_size = el_size;
	circular_buf_reset(cbuf);

	assert(circular_buf_empty(cbuf));

	return cbuf;
}

void circular_buf_free(cbuf_handle_t cbuf)
{
	assert(cbuf);
	free(cbuf);
}

void circular_buf_reset(cbuf_handle_t cbuf)
{
    assert(cbuf);

    cbuf->full = false;

    cbuf->head_idx = 0;
    cbuf->tail_idx = 0;
}

size_t circular_buf_size(cbuf_handle_t cbuf)
{
	assert(cbuf);

	size_t size = cbuf->max;

	if(!cbuf->full)
	{
		if(cbuf->head_idx >= cbuf->tail_idx)
		{
			size = cbuf->head_idx - cbuf->tail_idx;
		}
		else
		{
			size = cbuf->max + cbuf->head_idx - cbuf->tail_idx;
		}
	}

	return size;
}

size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
	assert(cbuf);

	return cbuf->max;
}

void circular_buf_put(cbuf_handle_t cbuf, void* data)
{
	assert(cbuf && cbuf->buffer);

    size_t offset = cbuf->head_idx * cbuf->el_size;
    memcpy( cbuf->buffer + offset, data, cbuf->el_size );

    advance_pointer(cbuf);
}

int circular_buf_put2(cbuf_handle_t cbuf, void* data)
{
    int r = -1;

    assert(cbuf && cbuf->buffer);

    if(!circular_buf_full(cbuf))
    {
	size_t offset = cbuf->head_idx * cbuf->el_size;
	memcpy( cbuf->buffer + offset, data, cbuf->el_size );
        
	advance_pointer(cbuf);
        r = 0;
    }

    return r;
}

int circular_buf_get(cbuf_handle_t cbuf, void** data)
{
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buf_empty(cbuf))
    {
	size_t offset = cbuf->tail_idx * cbuf->el_size;

	*data = cbuf->buffer + offset;

        retreat_pointer(cbuf);

        r = 0;
    }

    return r;
}

bool circular_buf_empty(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return (!cbuf->full && (cbuf->head_idx == cbuf->tail_idx));
}

bool circular_buf_full(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return cbuf->full;
}
#else
void cb_init(circular_buffer *cb, size_t capacity, size_t sz)
{
    cb->buffer = malloc(capacity * sz);
    if(cb->buffer == NULL)
        // handle error
    cb->buffer_end = (char *)cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
}

void cb_free(circular_buffer *cb)
{
    free(cb->buffer);
    // clear out other fields too, just to be safe
}

void cb_push_back(circular_buffer *cb, const void *item)
{
    if(cb->count == cb->capacity){
        // handle error
    }
    memcpy(cb->head, item, cb->sz);
    cb->head = (char*)cb->head + cb->sz;
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->count++;
}

void cb_pop_front(circular_buffer *cb, void *item)
{
    if(cb->count == 0){
        // handle error
    }
    memcpy(item, cb->tail, cb->sz);
    cb->tail = (char*)cb->tail + cb->sz;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;
}
#endif
