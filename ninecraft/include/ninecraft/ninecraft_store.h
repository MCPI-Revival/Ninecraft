#ifndef NINECRAFT_NINECRAFT_STORE_H
#define NINECRAFT_NINECRAFT_STORE_H

#include <stdbool.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_vector.h>
#include <ancmp/abi_fix.h>

typedef struct {
    void *vtable;
    int unknown1;
    int unknown2;
    int unknown3;
} ninecraft_store_t;

typedef struct {
    ninecraft_store_t *store;
} ninecraft_store_context_t;

void ninecraft_store_create(ninecraft_store_context_t *ret, android_string_t *str, void *listener);

void ninecraft_store_destory(void *ninecraft_store);

bool ninecraft_store_allows_query_purchases_on_startup(void *ninecraft_store);

EXTERN_SYSV_WRAPPER(ninecraft_store_get_store_id);
void ninecraft_store_get_store_id(android_string_t *ret, void *ninecraft_store);

void ninecraft_store_query_products(void *ninecraft_store, android_vector_t *products);

void ninecraft_store_purchase(void *ninecraft_store, android_string_gnu_t *name);

void ninecraft_store_query_purchases(void *ninecraft_store);

#endif