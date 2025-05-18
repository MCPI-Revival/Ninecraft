#ifndef NINECRAFT_NINECRAFT_HTTP_H
#define NINECRAFT_NINECRAFT_HTTP_H

typedef struct {
    void *vtable;
    void *jni_object;
    void *request;
} ninecraft_http_t;

void ninecraft_http_construct(ninecraft_http_t *http, void *request);

void ninecraft_http_send(ninecraft_http_t *http);

void ninecraft_http_abort(ninecraft_http_t *http);

void ninecraft_http_destroy(ninecraft_http_t *http);

#endif