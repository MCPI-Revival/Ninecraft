#include <ninecraft/game_parameters.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

game_parameters_t game_parameters = {
    (char *)NULL,   // home_path
    (char *)NULL,   // game_path
    (char *)NULL,   // server_level_file
    (char *)NULL,   // server_motd
    -1,             // server_port
    -1,             // server_max_players
};

static char cwd_path[1024];

void parse_game_parameters(int argc, char **argv) {
    int i;
    getcwd(cwd_path, sizeof(cwd_path));
    for (i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--game")) {
            if (++i < argc) {
                game_parameters.game_path = argv[i];
            }
        } else if (!strcmp(argv[i], "--home")) {
            if (++i < argc) {
                game_parameters.home_path = argv[i];
            }
#ifdef NINECRAFT_HEADLESS
        } else if (!strcmp(argv[i], "--level")) {
            if (++i < argc) {
                game_parameters.server_level_file = argv[i];
            }
        } else if (!strcmp(argv[i], "--motd")) {
            if (++i < argc) {
                game_parameters.server_motd = argv[i];
            }
        } else if (!strcmp(argv[i], "--port")) {
            if (++i < argc) {
                int port = atoi(argv[i]);
                if (port > 65535 || port < 1) {
                    printf("Port must be between 1 and 65535\n");
                    exit(1);
                }
                game_parameters.server_port = port;
            }
        } else if (!strcmp(argv[i], "--max-players")) {
            if (++i < argc) {
                int max_players = atoi(argv[i]);
                if (max_players < 1) {
                    printf("Max players must at least be 1\n");
                    exit(1);
                } else if (max_players > 65535) {
                    printf("Warning: max players has been set to a value greater than 65535. Expect errors\n");
                }
                game_parameters.server_max_players = max_players;
            }
#endif
        } else if (!strcmp(argv[i], "--help")) {
            printf("%s <args...>\n", argv[0]);
            printf("--home <path>: specifies the path to the userdata directory\n");
            printf("--game <path>: specifies the path to the gamedata directory\n");
#ifdef NINECRAFT_HEADLESS
            printf("--level <path>: specifies the file name of the level to host\n");
            printf("--motd <motd>: specifies the text to display as the server MOTD\n");
            printf("--port <port>: specifies what port to listen on (default: 19132)\n");
            printf("--max-players <count>: specifies the maximum player count (default: 10)\n");
#endif
            printf("--help: prints the usage of the command line arguments\n");
            exit(0);
        }
    }
    if (!game_parameters.game_path) {
        game_parameters.game_path = cwd_path;
    }
    if (!game_parameters.home_path) {
        game_parameters.home_path = cwd_path;
    }
#ifdef NINECRAFT_HEADLESS
    if (!game_parameters.server_level_file) {
        printf("Error: Level file name must be specified\n");
        exit(1);
    }
    if (!game_parameters.server_motd) {
        game_parameters.server_motd = "Ninecraft Server";
    }
    if (game_parameters.server_port == -1) {
        game_parameters.server_port = 19132;
    }
    if (game_parameters.server_max_players == -1) {
        game_parameters.server_max_players = 10;
    }
#endif
}