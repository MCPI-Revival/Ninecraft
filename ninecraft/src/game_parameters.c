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
    (char *)NULL,
    (char *)NULL
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
        } else if (!strcmp(argv[i], "--help")) {
            printf("%s <args...>\n", argv[0]);
            printf("--home <path>: specifies the path to the userdata directory\n");
            printf("--game <path>: specifies the path to the gamedata directory\n");
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
}