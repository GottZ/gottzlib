#ifndef gottz_lib_h
#define gottz_lib_h

#ifdef __cplusplus
extern "C"
{
#endif
#if 0
} /* unconfuse various editors */
#endif
#define GOTTZLIB_VERSION_MAJOR 0
#define GOTTZLIB_VERSION_MINOR 0
#define GOTTZLIB_VERSION_PATCH 1
#define GOTTZLIB_VERSION_STRING "0.0.1"
////////////////////////////////////////////////////////////////////////////////

#ifndef GOTTZ_FREAD_CHUNK_SIZE
#define GOTTZ_FREAD_CHUNK_SIZE 256
#endif

#include <stdlib.h>

void* gottz_quick_pread(size_t* buffer_size, const char* command);

// returns buffer on success and 0 on failure
// on failure, buffer_size 1 on memory allocation error
// on failure, buffer_size 2 on stream access error. can be further evaluated via ferror(stream)
// chunk_size will exponentially grow during read when ever the boundary is hit
void* gottz_fread_to_heap(size_t* buffer_size, FILE* stream);

// returns buffer on success and 0 on failure
// on failure, buffer_size 1 on memory allocation error
// on failure, buffer_size 2 on stream access error. can be further evaluated via ferror(stream)
// chunk_size will exponentially grow during read when ever the boundary is hit
void* gottz_fread_to_heap_ex(size_t* buffer_size, size_t chunk_size, FILE* stream);

////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
