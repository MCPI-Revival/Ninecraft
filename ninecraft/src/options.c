#include <stdio.h>
#include <ninecraft/options.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void ninecraft_set_default_options(ninecraft_options_t *options, char *file_path) {
    ninecraft_set_option(options, "mp_username", "Steve", false);
    ninecraft_set_option(options, "mp_server", "Steve", false);
    ninecraft_set_option(options, "mp_server_visible_default", "true", false);
    ninecraft_set_option(options, "gfx_fancygraphics", "true", false);
    ninecraft_set_option(options, "gfx_lowquality", "false", false);
    ninecraft_set_option(options, "ctrl_sensitivity", "1.0", false);
    ninecraft_set_option(options, "ctrl_invertmouse", "false", false);
    ninecraft_set_option(options, "ctrl_islefthanded", "false", false);
    ninecraft_set_option(options, "ctrl_usetouchscreen", "false", false);
    ninecraft_set_option(options, "ctrl_usetouchjoypad", "false", false);
    ninecraft_set_option(options, "feedback_vibration", "false", false);
    ninecraft_set_option(options, "game_difficulty", "4", false);
    ninecraft_write_options_file(options, file_path);
}

void ninecraft_set_option(ninecraft_options_t *options, char *name, char *value, bool override) {
    if (options != NULL && name != NULL && value != NULL) {
        size_t value_length = strlen(value);
        for (size_t i = 0; i < options->length; ++i) {
            if (strcmp(options->options[i].name, name) == 0) {
                if (override) {
                    ninecraft_option_t *option = options->options + i;
                    if (strlen(option->value) < value_length) {
                        free(option->value);
                        option->value = (char *)malloc(value_length + 1);
                    }
                    memset(option->value, value, value_length);
                    option->value[value_length] = '\0';
                }
                return;
            }
        }
        if (options->options == NULL || options->capasity == 0) {
            options->capasity = 10;
            options->options = (ninecraft_option_t *)malloc(sizeof(ninecraft_option_t) * 10);
        } else if (options->capasity < options->length + 1) {
            options->capasity += 10;
            options->options = (ninecraft_option_t *)realloc(options->options, sizeof(ninecraft_option_t) * options->capasity);
        }
        ninecraft_option_t *option = options->options + options->length;
        size_t name_length = strlen(name);
        option->name = (char *)malloc(name_length + 1);
        option->name[name_length] = '\0';
        option->value = (char *)malloc(value_length + 1);
        option->value[value_length] = '\0';
        memcpy(option->name, name, name_length);
        memcpy(option->value, value, value_length);
        ++options->length;
    }
}

void ninecraft_read_options_file(ninecraft_options_t *options, char *file_path) {
    FILE *stream = fopen(file_path, "r");
    if (stream != NULL) {
        fseek(stream, 0, SEEK_END);
        size_t buffer_size = ftell(stream);
        fseek(stream, 0, SEEK_SET);
        char *buffer = (char *)malloc(buffer_size);
        if (buffer != NULL) {
            if (fread(buffer, 1, buffer_size, stream) > 0) {
                size_t size = 0;
                char *name = NULL;
                bool is_value = false;
                for (size_t i = 0; i < buffer_size; ++i) {
                    if (buffer[i] == '\n') {
                        if (is_value) {
                            buffer[i] = '\0';
                            ninecraft_set_option(options, name, buffer + i - size, true);
                        }
                        size = 0;
                        is_value = false;
                        name = NULL;
                    } else if (buffer[i] == ':') {
                        buffer[i] = '\0';
                        name = buffer + i - size;
                        size = 0;
                        is_value = true;
                    } else {
                        ++size;
                    }
                }
                if (is_value) {
                    char *value = (char *)malloc(size + 1);
                    if (value != NULL) {
                        memcpy(value, buffer + buffer_size - size, size);
                        value[size] = '\0';
                        ninecraft_set_option(options, name, value, true);
                        free(value);
                    }
                }
            }
            free(buffer);
        }
        fclose(stream);
    }
}

void ninecraft_write_options_file(ninecraft_options_t *options, char *file_path) {
    FILE *stream = fopen(file_path, "w");
    if (stream != NULL) {
        for (size_t i = 0; i < options->length; ++i) {
            fwrite(options->options[i].name, 1, strlen(options->options[i].name), stream);
            fputc(':', stream);
            fwrite(options->options[i].value, 1, strlen(options->options[i].value), stream);
            fputc('\n', stream);
        }
        fclose(stream);
    }
}