#ifndef XMALLOC_H__
#define XMALLOC_H__

#include <stdlib.h>

void *malloc_or_exit(size_t nbytes, const char *file, int line);

#define xmalloc(nbytes) malloc_or_exit(nbytes, __FILE__, __LINE__);

#endif
// endif H_XMALLOC_H