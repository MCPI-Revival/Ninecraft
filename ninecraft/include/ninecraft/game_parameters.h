#ifndef NINECRAFT_GAME_PARAMETERS_H
#define NINECRAFT_GAME_PARAMETERS_H

typedef struct {
    char *home_path;
    char *game_path;
    
    // Server parameters
    char *server_level_file;
    char *server_motd;
    int server_port;
    int server_max_players;
} game_parameters_t;

extern game_parameters_t game_parameters;

void parse_game_parameters(int argc, char **argv);

#endif