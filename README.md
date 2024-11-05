# A personal C snippet collection put into a single C File

## Status report

As of right now, this is just the start of collecting my utility functions.  
Testing was mostly done during development. I intend to add proper tests over time tho.

## what does this do?

see [test.c](https://github.com/GottZ/gottzlib/blob/root/test.c) and [gottzlib.h](https://github.com/GottZ/gottzlib/blob/root/gottzlib.h) for now.  
for now, it just contains the following symbols:
```c
// stability: 8/10 - not prone to symbol change. behavior may be improved later.
void* gottz_quick_pread(size_t* buffer_size, const char* command)
```
I consider this stable except for the missing `errno` usage.  
I'll be using `errno` instead eventually.  
It writes out to `buffer_size`, to let you know the binary content size, of the returned heap allocation.  
if anything goes wrong, it will return a null pointer and set a error value to `buffer_size`.  
Right now, the underlying implementation also does `perror` calls I have to take out.

```c
// stability: 8/10 - same state as gottz_quick_pread
void* gottz_fread_to_heap(size_t* buffer_size, FILE* stream)
```
It just calls the following with `GOTTZ_FREAD_CHUNK_SIZE` as default chunk size. (you can override it):
```c
// stability: 2/10 - not the final design yet. Only use with version pinning or code review!
void* gottz_fread_to_heap_ex(size_t* buffer_size, size_t chunk_size, FILE* stream)
```
This simply this simply wraps `fread` and reads the file stream into a dynamic heap allocation.  
I plan on adding extents to specify max buffer size and a timeout.  
As of right now, I don't need that tho.

I'll provide automated documentation at a later time.  
Also proper language server support.

## Testing

`test.c` is a polyglot. you can just execute it from your shell and it will magically compile and run itself.
```bash
chmod +x test.c
./test.c
```

## Contribution

### Experience

If you see anything that could need some tweaking or could be simplified even further under the hood of my utilities, feel free to enlighten me either via an Issue or a Pull Request.  
Be wary tho, that I will not just lightly accept Pull Requests, as I first have to review them thoroughly, which in C, is a risky thing to miss out on.

#### CMake

I literally know nothing about CMake yet.  
This is mostly because I basically stopped working with C around 2012 and always used to use plain Makefiles instead.  
Feel free to add CMake stuff here, so it can easily be used in CMake projects.  
I have no clue how, nor this is my focus right now.  
If you want it, feel free to participate.

#### Language Server integration

If you see anything that could be improved for language server integration, just let me know!

### Events

If you want a webhook or so, to be informed about updates, tags and releases, just let me know your endpoint and we can set it up.  
This is particularily useful, in case you plan to bundle this into a package manager eventually.  
(As of right now, I doubt anyone cares tho, as none of my current API Surface is particularily frozen yet)

### Contact

Just reach out to me over [here](https://contact.gottz.de) for private messages.
