#pragma once

typedef struct {
    char filler[4];
} android_string;

void to_str(void *str, char *cstr, void *handle);
