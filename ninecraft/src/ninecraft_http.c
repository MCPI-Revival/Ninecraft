#include <ninecraft/ninecraft_http.h>
#include <stdio.h>

void *ninecraft_http_vtable[] = {
    (void *)ninecraft_http_destroy,
    (void *)ninecraft_http_destroy
};

void ninecraft_http_construct(ninecraft_http_t *http, void *request) {
    puts("NINECRAFT HTTP: construct");
    http->request = request;
    http->vtable = ninecraft_http_vtable;
}

void ninecraft_http_send(ninecraft_http_t *http) {
    puts("NINECRAFT HTTP: send");
}

void ninecraft_http_abort(ninecraft_http_t *http) {
    puts("NINECRAFT HTTP: abort");
}

void ninecraft_http_destroy(ninecraft_http_t *http) {
    puts("NINECRAFT HTTP: destroy");
}