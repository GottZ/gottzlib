#include "gottzlib.h"

#define GOTTZLIB_IMPL_VERSION_MAJOR 0
#define GOTTZLIB_IMPL_VERSION_MINOR 0
#define GOTTZLIB_IMPL_VERSION_PATCH 2

#if (GOTTZLIB_VERSION_MAJOR != GOTTZLIB_IMPL_VERSION_MAJOR)\
|| (GOTTZLIB_VERSION_MINOR != GOTTZLIB_IMPL_VERSION_MINOR)\
|| (GOTTZLIB_VERSION_PATCH != GOTTZLIB_IMPL_VERSION_PATCH)
#error "gottzlib version mismatch between gottzlib.c and gottzlib.h"
#endif

#import <linux/limits.h>
#import <unistd.h>

const char* ERR_INSUFFICIENT_MEMORY = "insufficient memory";
const char* ERR_FILE_ERROR = "error encountered during fread";

void* gottz_quick_pread(size_t* buffer_size, const char* command) {
	FILE* pipe = popen(command, "r");
	if (!pipe) {
		perror("popen failed");
		return 0;
	}

	char* buffer = gottz_fread_to_heap(buffer_size, pipe);
	if (!buffer) {
		perror("encountered error reading stream to heap");
		pclose(pipe);
		return 0;
	}

	pclose(pipe);

	return buffer;
}

void* gottz_fread_to_heap(size_t* buffer_size, FILE* stream) {
	return gottz_fread_to_heap_ex(buffer_size, GOTTZ_FREAD_CHUNK_SIZE, stream);
}

void* gottz_fread_to_heap_ex(size_t* buffer_size, size_t chunk_size, FILE* stream) {
	*buffer_size = 0;
	char* buffer = malloc(chunk_size);
	if (!buffer) {
		perror(ERR_INSUFFICIENT_MEMORY);
		*buffer_size = 1;
		return 0;
	}

	size_t i = 0;
	int err = 0;

	while(!feof(stream) && !(err = ferror(stream))) {
		size_t read = fread(buffer + i, sizeof(char), chunk_size - i, stream);
		i += read;
		if (i == chunk_size) {
			chunk_size *= 2;
			char* new_buffer = realloc(buffer, chunk_size);
			if (!new_buffer) {
				perror(ERR_INSUFFICIENT_MEMORY);
				free(buffer);
				*buffer_size = 1;
				return 0;
			}
			buffer = new_buffer;
		}
	}

	if (err) {
		perror(ERR_FILE_ERROR);
		free(buffer);
		*buffer_size = 2;
		return 0;
	}

	if (chunk_size != i + 1) {
		char* new_buffer = realloc(buffer, i + 1);
		if (!new_buffer) {
			perror(ERR_INSUFFICIENT_MEMORY);
			free(buffer);
			*buffer_size = 1;
			return 0;
		}
		buffer = new_buffer;
	}
	buffer[i] = 0;

	*buffer_size = i;

	return buffer;
}

char exec_path[PATH_MAX] = {0};

const char* gottz_get_exec_path() {
	if (*exec_path) return exec_path;
	int len = readlink("/proc/self/exe", exec_path, PATH_MAX);
	// logic somewhat taken from https://stackoverflow.com/a/63857510/1519836
	if (len <= 0 || len == PATH_MAX) {
		return 0;
	}
	return exec_path;
}
