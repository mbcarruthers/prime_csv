#ifndef LIST_H__
#define LIST_H__

#include "xmalloc.h"

typedef struct prime_ {
    unsigned long value;
    struct prime_ * next;
} prime_;

typedef struct {
    size_t len;
    prime_ * front;
} primes_l;

primes_l empty_list(void);

void list_clear(primes_l * l);

void list_print(primes_l * l);

void list_append(primes_l * l, unsigned long value);

void list_insert_before(primes_l * l , unsigned long a, unsigned long b);

void list_delete(primes_l * l , unsigned long value);

void list_apply(primes_l * l , int (*fn_ptr)(unsigned long));

void list_reduce(primes_l * l , int (*fn_ptr)(unsigned long, unsigned long));

#endif // LIST_H__