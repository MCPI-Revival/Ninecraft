#ifndef NINECRAFT_OPTIONS_H
#define NINECRAFT_OPTIONS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char *name;
    char *value;
} ninecraft_option_t;

typedef struct {
    ninecraft_option_t *options;
    size_t length;
    size_t capasity;
} ninecraft_options_t;

void ninecraft_set_default_options(ninecraft_options_t *options, char *file_path);

void ninecraft_set_option(ninecraft_options_t *options, char *name, char *value, bool override);

void ninecraft_read_options_file(ninecraft_options_t *options, char *file_path);

void ninecraft_write_options_file(ninecraft_options_t *options, char *file_path);

#endif