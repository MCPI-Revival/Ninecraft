#pragma once

typedef struct {
    char filler[30];
} android_string;

void to_str(void *str, char *cstr, void *handle);
