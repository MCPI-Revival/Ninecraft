#ifndef NINECRAFT_GAME_PARAMETERS_H
#define NINECRAFT_GAME_PARAMETERS_H

typedef struct {
    char *home_path;
    char *game_path;
} game_parameters_t;

extern game_parameters_t game_parameters;

#endif