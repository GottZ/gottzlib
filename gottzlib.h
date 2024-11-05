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
#define GOTTZLIB_VERSION_PATCH 2
#define GOTTZLIB_VERSION_STRING "0.0.2"
////////////////////////////////////////////////////////////////////////////////

#ifndef GOTTZ_FREAD_CHUNK_SIZE
#define GOTTZ_FREAD_CHUNK_SIZE 256
#endif

#include <stdlib.h>

// stability: 8/10 - not prone to symbol change. behavior may be improved later.
void* gottz_quick_pread(size_t* buffer_size, const char* command);

// returns buffer on success and 0 on failure
// on failure, buffer_size 1 on memory allocation error
// on failure, buffer_size 2 on stream access error. can be further evaluated via ferror(stream)
// chunk_size will exponentially grow during read when ever the boundary is hit
// the returned buffer will be null terminated.
// stability: 8/10 - same state as gottz_quick_pread
void* gottz_fread_to_heap(size_t* buffer_size, FILE* stream);

// same as gottz_fread_to_heap
// chunk_size will exponentially grow during read when ever the boundary is hit
// stability: 2/10 - not the final design yet. Only use with version pinning or code review!
void* gottz_fread_to_heap_ex(size_t* buffer_size, size_t chunk_size, FILE* stream);

// use https://github.com/gpakosz/whereami instead, in case you want to use this outside linux
// it simply reads /proc/self/exe which is not stantardized
// keep in mind, linux allows executing rename on /proc/self/exe, so this is only as good as it get's.
// preferrably, only run this once during init of your application. especially if you store additional data in your binary.
// essentially, there is no safe way to acquire the binary path, as it can be dangling in kernel space after unlink.
// stability: 9/10 - might add different platforms later but the call won't change.
const char* gottz_get_exec_path();

////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
