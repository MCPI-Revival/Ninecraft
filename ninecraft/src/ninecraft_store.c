#include <stdio.h>
#include <ninecraft/ninecraft_store.h>

void *ninecraft_store_vtable[] = {
    (void *)ninecraft_store_destory,
    (void *)ninecraft_store_destory,
    (void *)ninecraft_store_allows_query_purchases_on_startup,
    (void *)GET_SYSV_WRAPPER(ninecraft_store_get_store_id),
    (void *)ninecraft_store_query_products,
    (void *)ninecraft_store_purchase,
    (void *)ninecraft_store_query_purchases,
};

SYSV_WRAPPER(ninecraft_store_create, 2);
void ninecraft_store_create(ninecraft_store_context_t *ret, void *listener) {
    puts("NINECRAFT_STORE: create");
    ret->store = (ninecraft_store_t *)malloc(sizeof(ninecraft_store_t));
    ret->store->vtable = ninecraft_store_vtable;
}

void ninecraft_store_destory(void *ninecraft_store) {
    puts("NINECRAFT_STORE: destory");
}

bool ninecraft_store_allows_query_purchases_on_startup(void *ninecraft_store) {
    puts("NINECRAFT_STORE: allows_query_purchases_on_startup");
    return false;
}

SYSV_WRAPPER(ninecraft_store_get_store_id, 2);
void ninecraft_store_get_store_id(android_string_t *ret, void *ninecraft_store) {
    puts("NINECRAFT_STORE: get_store_id");
    android_string_cstr(ret, "NinecraftStore");
}

void ninecraft_store_query_products(void *ninecraft_store, android_vector_t *products) {
    puts("NINECRAFT_STORE: query_products");
}

void ninecraft_store_purchase(void *ninecraft_store, android_string_gnu_t *name) {
    puts("NINECRAFT_STORE: purchase");
}

void ninecraft_store_query_purchases(void *ninecraft_store) {
    puts("NINECRAFT_STORE: query_purchases");
}
