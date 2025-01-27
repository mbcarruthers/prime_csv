#ifndef LIST_H__
#define LIST_H__
#include "xmalloc.h"

// list item for prime value
typedef struct {
    unsigned long value;
    struct prime * next;
} prime_;

// primes list
typedef struct {
    struct prime_ * head;
    struct prime_ * tail;
} primes_l;


static inline prime_ * create_prime(unsigned long value) {
    prime_ * p = (prime_*)xmalloc(sizeof(prime_));
    p->value = value;
    p->next = NULL;
    return p;
}

primes_l * create_list(unsigned long value) {
    primes_l * l = (primes_l*)xmalloc(sizeof(primes_l));
    l->head = create_prime(value);
    l->tail = l->head;
    return l;
}

void pushb(primes_l * l , unsigned long value) {
   l->head->next = create_prime(value);
   l->head = l->head->next;
   l->head->next = NULL;
}

#endif // LIST_H__