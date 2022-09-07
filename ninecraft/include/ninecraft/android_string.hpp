#pragma once

typedef struct {
    char filler[4];
} android_string;

char *to_str(void *str, char *cstr, void *handle);