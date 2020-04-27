#include<string.h>

#include "mac/cvector.h"



static int _cvector_realloc( cvector_t* self, size_t new_count )
{
	int err = 0;

	size_t new_sz = new_count * (self->el_size);
	char* new_data = (char*)realloc( self->data, new_sz );

	if( new_data )
	{
		self->reserved_size = new_count;
		self->data = new_data;
	}
	else
		err = 1;

	return err;
}

int cvector_init( cvector_t* self, size_t el_size ) 
{
	int err = 0;

	self->data = NULL;
	self->count = 0;
	self->el_size = el_size;

	self->reserved_size = 10;
	_cvector_realloc( self, self->reserved_size );

	return err;
}

size_t cvector_size( cvector_t* self )
{
	return self->count;
}

int cvector_finish( cvector_t* self )
{
	int err = 0;

	free( self->data );

	return err;
}

int cvector_resize( cvector_t* self, size_t nelems )
{
	int err = 0;

	err = _cvector_realloc( self, nelems );

	return err;
}

#if 0
bool _cvector_append( cvector_t* vector, const void* values, size_t count) 
{
	const size_t count_new = count + vc_vector_count(vector);

	if (vc_vector_max_count(vector) < count_new) {
		size_t max_count_to_reserved = vc_vector_max_count(vector) * GROWTH_FACTOR;
		while (count_new > max_count_to_reserved) {
			max_count_to_reserved *= GROWTH_FACTOR;
		}

		if (!vc_vector_realloc(vector, max_count_to_reserved)) {
			return false;
		}
	}

	if (memcpy(vector->data + vector->count * vector->element_size,
				values,
				vector->element_size * count) == NULL) {
		return false;
	}

	vector->count = count_new;
	return true;
}
#endif

void* cvector_element_at( cvector_t* self, size_t idx )
{
	return self->data + (idx* self->el_size);
}


int cvector_push_back( cvector_t* self, void* data )
{
	int err = 0;

	if( cvector_size( self ) == self->reserved_size )
		_cvector_realloc( self, 2* self->reserved_size );

	memcpy( self->data + (self->count * self->el_size), data, self->el_size);
	self->count++;

	return err;
}

int cvector_data( cvector_t* self, void** data )
{
	int err = 0;

	*data = self->data;

	return err = 0;
}

