#ifndef MAC_VECTOR
#define MAC_VECTOR


#ifdef __cplusplus
extern "C"
}
#endif
#include <stddef.h>
#include <stdlib.h>

typedef struct _cvector_t 
{
	size_t el_size;
	size_t reserved_size;
	size_t count;
	char* data;

} cvector_t;


int cvector_init( cvector_t* self, size_t el_size );

size_t cvector_size( cvector_t* self );

int cvector_finish( cvector_t* self );

void* cvector_element_at( cvector_t* self, size_t idx  );

int cvector_push_back( cvector_t* self, void* data );

int cvector_data( cvector_t* self, void** data );

#ifdef __cplusplus
}
#endif

#endif
