#include <string.h>

#include <ninecraft/sound_repo.h>

void get_sound(char **arr, char *name) {
    if (strcmp(name, "random.pop2") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_pop2";
    } else if (strcmp(name, "step.cloth") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_cloth1";
        arr[2] = "PCM_cloth2";
        arr[3] = "PCM_cloth3";
        arr[4] = "PCM_cloth4";
    } else if (strcmp(name, "step.grass") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_grass1";
        arr[2] = "PCM_grass2";
        arr[3] = "PCM_grass3";
        arr[4] = "PCM_grass4";
    } else if (strcmp(name, "step.gravel") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_gravel1";
        arr[2] = "PCM_gravel2";
        arr[3] = "PCM_gravel3";
        arr[4] = "PCM_gravel4";
    } else if (strcmp(name, "step.sand") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_sand1";
        arr[2] = "PCM_sand2";
        arr[3] = "PCM_sand3";
        arr[4] = "PCM_sand4";
    } else if (strcmp(name, "step.stone") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_stone1";
        arr[2] = "PCM_stone2";
        arr[3] = "PCM_stone3";
        arr[4] = "PCM_stone4";
    } else if (strcmp(name, "step.wood") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_wood1";
        arr[2] = "PCM_wood2";
        arr[3] = "PCM_wood3";
        arr[4] = "PCM_wood4";
    } else if (strcmp(name, "random.click") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_click";
    } else if (strcmp(name, "random.explode") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_explode";
    } else if (strcmp(name, "random.splash") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_splash";
    } else if (strcmp(name, "random.door_open") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_door_open";
    } else if (strcmp(name, "random.door_close") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_door_close";
    } else if (strcmp(name, "random.pop") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_pop";
    } else if (strcmp(name, "random.hurt") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_hurt";
    } else if (strcmp(name, "random.glass") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_glass1";
        arr[2] = "PCM_glass2";
        arr[3] = "PCM_glass3";
    } else if (strcmp(name, "mob.sheep") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_sheep1";
        arr[2] = "PCM_sheep2";
        arr[3] = "PCM_sheep3";
    } else if (strcmp(name, "mob.pig") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_pig1";
        arr[2] = "PCM_pig2";
        arr[3] = "PCM_pig3";
    } else if (strcmp(name, "mob.pigdeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_pigdeath";
    } else if (strcmp(name, "mob.chicken") == 0) {
        arr[0] = 2;
        arr[1] = "PCM_chicken2";
        arr[2] = "PCM_chicken3";
    } else if (strcmp(name, "mob.chickenhurt") == 0) {
        arr[0] = 2;
        arr[1] = "PCM_chickenhurt1";
        arr[2] = "PCM_chickenhurt2";
    } else if (strcmp(name, "mob.cow") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_cow1";
        arr[2] = "PCM_cow2";
        arr[3] = "PCM_cow3";
        arr[4] = "PCM_cow4";
    } else if (strcmp(name, "mob.cowhurt") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_cowhurt1";
        arr[2] = "PCM_cowhurt2";
        arr[3] = "PCM_cowhurt3";
    } else if (strcmp(name, "mob.zombie") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_zombie1";
        arr[2] = "PCM_zombie2";
        arr[3] = "PCM_zombie3";
    } else if (strcmp(name, "mob.zombiepig.zpig") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_zpig1";
        arr[2] = "PCM_zpig2";
        arr[3] = "PCM_zpig3";
        arr[4] = "PCM_zpig4";
    } else if (strcmp(name, "mob.zombiepig.zpigangry") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_zpigangry1";
        arr[2] = "PCM_zpigangry2";
        arr[3] = "PCM_zpigangry3";
        arr[4] = "PCM_zpigangry4";
    } else if (strcmp(name, "mob.zombiepig.zpigdeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_zpigdeath";
    } else if (strcmp(name, "mob.zombiepig.zpighurt") == 0) {
        arr[0] = 2;
        arr[1] = "PCM_zpighurt1";
        arr[2] = "PCM_zpighurt2";
    } else if (strcmp(name, "mob.zombiedeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_zombiedeath";
    } else if (strcmp(name, "mob.zombiehurt") == 0) {
        arr[0] = 2;
        arr[1] = "PCM_zombiehurt1";
        arr[2] = "PCM_zombiehurt2";
    } else if (strcmp(name, "random.bow") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_bow";
    } else if (strcmp(name, "random.bowhit") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_bowhit1";
        arr[2] = "PCM_bowhit2";
        arr[3] = "PCM_bowhit3";
        arr[4] = "PCM_bowhit4";
    } else if (strcmp(name, "damage.fallbig") == 0) {
        arr[0] = 2;
        arr[1] = "PCM_fallbig1";
        arr[2] = "PCM_fallbig2";
    } else if (strcmp(name, "damage.fallsmall") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_fallsmall";
    } else if (strcmp(name, "mob.skeleton") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_skeleton1";
        arr[2] = "PCM_skeleton2";
        arr[3] = "PCM_skeleton3";
    } else if (strcmp(name, "mob.skeletondeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_skeletondeath";
    } else if (strcmp(name, "mob.skeletonhurt") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_skeletonhurt1";
        arr[2] = "PCM_skeletonhurt2";
        arr[3] = "PCM_skeletonhurt3";
        arr[4] = "PCM_skeletonhurt4";
    } else if (strcmp(name, "mob.spider") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_spider1";
        arr[2] = "PCM_spider2";
        arr[3] = "PCM_spider3";
        arr[4] = "PCM_spider4";
    } else if (strcmp(name, "mob.spiderdeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_spiderdeath";
    } else if (strcmp(name, "mob.creeper") == 0) {
        arr[0] = 4;
        arr[1] = "PCM_creeper1";
        arr[2] = "PCM_creeper2";
        arr[3] = "PCM_creeper3";
        arr[4] = "PCM_creeper4";
    } else if (strcmp(name, "mob.creeperdeath") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_creeperdeath";
    } else if (strcmp(name, "random.eat") == 0) {
        arr[0] = 3;
        arr[1] = "PCM_eat1";
        arr[2] = "PCM_eat2";
        arr[3] = "PCM_eat3";
    } else if (strcmp(name, "random.fuse") == 0) {
        arr[0] = 1;
        arr[1] = "PCM_fuse";
    } else {
        arr[0] = 0;
    }
    return arr;
}